#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include "SG_ServerBase.h"
#include "SG_Config.h"
#include "SG_ClientSession.h"
#include "Tools/SG_DataConverter.h"
#include "Packets/PacketBaseMessage.h"
#include <Tools/SG_Logger.h>

MySQLConnection *SG_ClientSession::SQLConn = nullptr;
SG_Config *SG_ClientSession::conf = nullptr;


SG_ClientSession::SG_ClientSession(boost::asio::io_service &rService, boost::asio::strand &rStrand, boost::shared_ptr<SG_ServerBase> pServer): m_Socket(rService), m_Strand(rStrand), m_Server(pServer), m_SocketTimout(rService), m_Player(boost::make_shared<SG_Client>())
{
	Socketstatus = false;
}

SG_ClientSession::~SG_ClientSession()
{

}

// ------------------------------------------------------------------ //

boost::asio::ip::tcp::socket& SG_ClientSession::getSocket() { return m_Socket; }

void SG_ClientSession::StartConnection()
{
	if (!m_Server->OnClientConnected(shared_from_this()))
		return SG_ClientSession::DisconnectClient();

	m_Strand.post(boost::bind(&SG_ClientSession::Read, shared_from_this()));

	m_SocketTimout.expires_from_now(boost::posix_time::milliseconds(conf->SocketTimeout));
	m_SocketTimout.async_wait(m_Strand.wrap(boost::bind(&SG_ClientSession::HandleTimeout, shared_from_this())));
}

void SG_ClientSession::DisconnectClient()
{
	m_SocketTimout.cancel();
	m_Server->OnClientDisconnect(shared_from_this());

	boost::system::error_code ec;
	m_Socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
	m_Socket.close();
}


void SG_ClientSession::SendPacketStruct(const TS_MESSAGE* packet)
{
	if(packet->id == 2105)
	{
		std::stringstream ss;
		SG_DataConverter::BytebufferToString(reinterpret_cast<uint8_t*>(&packet), packet->size, ss);
		SG_Logger::instance().log(ss.str(), SG_Logger::kLogLevelPacket);
	}
	boost::asio::async_write(m_Socket, boost::asio::buffer(packet,packet->size), m_Strand.wrap(boost::bind(&SG_ClientSession::HandleSend, shared_from_this(), boost::asio::placeholders::error)));
}
// ------------------------------------------------------------------ //


void SG_ClientSession::Read()
{
	boost::shared_ptr<std::vector<uint8_t>> pBuffer(new std::vector<uint8_t>(sizeof(uint16_t)));
	boost::asio::async_read(m_Socket, boost::asio::buffer(*pBuffer, conf->MaxPacketSize), boost::asio::transfer_exactly(sizeof(uint16_t)), m_Strand.wrap(boost::bind(&SG_ClientSession::HandleRecvHeader, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, pBuffer)));
}

void SG_ClientSession::HandleRecvHeader(const boost::system::error_code &rEC, std::size_t stSize, boost::shared_ptr<std::vector<uint8_t>> pBuffer)
{
	if (rEC || !stSize)
		return SG_ClientSession::DisconnectClient();

	Socketstatus = true;
	m_SocketTimout.expires_from_now(boost::posix_time::milliseconds(conf->SocketTimeout));

	uint16_t Packetsize = *reinterpret_cast<uint16_t *>(pBuffer->data());
	if (Packetsize < conf->MinPacketSize || Packetsize > conf->MaxPacketSize)
	{
		std::cout << "Packetsize is not in valid space [" << Packetsize << "]" << std::endl;
		//return SG_ClientSession::DisconnectClient();
	}
	pBuffer->clear();
	pBuffer->resize(Packetsize);
	boost::asio::async_read(m_Socket, boost::asio::buffer(*pBuffer, Packetsize - sizeof(uint16_t)), boost::asio::transfer_exactly(Packetsize - sizeof(uint16_t)), m_Strand.wrap(boost::bind(&SG_ClientSession::HandleRecvBody, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, pBuffer)));
}

void SG_ClientSession::HandleRecvBody(const boost::system::error_code &rEC, std::size_t stSize, boost::shared_ptr<std::vector<uint8_t>> pBuffer)
{
	//boost::shared_ptr<SG_MemoryReader> pReader(new SG_MemoryReader(pBuffer));
	pBuffer->insert(pBuffer->begin(), static_cast<uint8_t>(stSize & 0xff));
	pBuffer->insert(pBuffer->begin() + 1, static_cast<uint8_t>((stSize >> 8) & 0xff));

	TS_MESSAGE* pack = reinterpret_cast<TS_MESSAGE*>(pBuffer->data());
	if (!m_Server->OnPacketReceived(shared_from_this(), pack))
		return SG_ClientSession::DisconnectClient();
	pBuffer->clear();
	m_Strand.post(boost::bind(&SG_ClientSession::Read, shared_from_this()));
}

void SG_ClientSession::HandleSend(const boost::system::error_code &rEC)
{
	if (rEC)
	{
		std::cout << "[" << __FUNCTION__ << "] Boost error [" << rEC << "]" << std::endl;
		SG_ClientSession::DisconnectClient();
	}
}

void SG_ClientSession::HandleTimeout()
{
	if (m_SocketTimout.expires_at() <= boost::asio::deadline_timer::traits_type::now())
	{
		if (Socketstatus)
		{
			Socketstatus = false;
		}
		else
		{
			//std::cout << "[" << __FUNCTION__ << "] Client socket timeout" << std::endl;
			return SG_ClientSession::DisconnectClient();
		}

		m_SocketTimout.expires_from_now(boost::posix_time::milliseconds(conf->SocketTimeout));
	}

	m_SocketTimout.async_wait(m_Strand.wrap(boost::bind(&SG_ClientSession::HandleTimeout, shared_from_this())));
}