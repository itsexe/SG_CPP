#ifndef SG_CLIENTSESSION
#define SG_CLIENTSESSION
#pragma once

#include <vector>
#include <cstdint>
#include "boost/asio.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Constructors/SG_Client.h"
#include "boost/asio/ip/address_v4.hpp"
#include "Packets/PacketBaseMessage.h"
#include "Tools/Database/Database.h"
#include "SG_Config.h"

/*++
Class for handling client sessions.
--*/

class SG_ServerBase;

class SG_ClientSession : public boost::enable_shared_from_this<SG_ClientSession>
{

public:
	SG_ClientSession(boost::asio::io_service &Service, boost::asio::strand &Strand, boost::shared_ptr<SG_ServerBase>);
	~SG_ClientSession();

	boost::asio::ip::tcp::socket& getSocket();

	void StartConnection();
	void DisconnectClient();
	void SendPacketStruct(const TS_MESSAGE* packet);
	boost::shared_ptr<SG_Client> m_Player;
	static MySQLConnection* SQLConn;
	static SG_Config* conf;

private:
	bool isStopped();
	bool isError();

	void Read();
	void HandleRecvHeader(const boost::system::error_code &Errorcode, std::size_t Packetsize, boost::shared_ptr<std::vector<uint8_t>> Buffer);
	void HandleRecvBody(const boost::system::error_code &Errorcode, std::size_t Packetsize, boost::shared_ptr<std::vector<uint8_t>> Buffer);
	void HandleSend(const boost::system::error_code &Errorcode);

	void HandleTimeout();

	boost::asio::ip::tcp::socket m_Socket;
	boost::shared_ptr<SG_ServerBase> m_Server;
	boost::asio::strand &m_Strand;
	boost::asio::deadline_timer m_SocketTimout;
	bool Socketstatus;
};
#endif