#include "SG_ServerBase.h"
#include <iostream>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/bind.hpp>
#include "SG_Config.h"
#include <Tools/SG_Logger.h>

SG_ServerBase::SG_ServerBase()
	: m_Acceptor(m_Service), m_Strand(m_Service)
{

}

SG_ServerBase::~SG_ServerBase()
{
	m_Acceptor.close();
	m_Threadpool.join_all();
	m_Service.stop();
}

// ------------------------------------------------------------------ //

bool SG_ServerBase::InitServer(const std::string &strIP, uint32_t uiPort, int32_t iThreadcount)
{
	if (strIP.empty() || !uiPort)
	{
		std::cout << "[" << __FUNCTION__ << "] Wrong IP or Port passed." << std::endl;
		return false;
	}
	std::stringstream ss_Port;
	ss_Port << uiPort;

	boost::asio::ip::tcp::resolver resolver(m_Service);
	boost::asio::ip::tcp::resolver::query query(strIP, ss_Port.str());
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

	boost::system::error_code ec;
	m_Acceptor.open(endpoint.protocol());
	m_Acceptor.bind(endpoint, ec);
	m_Acceptor.listen(boost::asio::socket_base::max_connections, ec);
	m_Acceptor.set_option(boost::asio::ip::tcp::no_delay(true));

	if (ec)
	{
		std::cout << "[" << __FUNCTION__ "] Boost error [" << ec << "]" << std::endl;
		return false;
	}

	if (!iThreadcount)
	{
		for (decltype(boost::thread::hardware_concurrency()) i = 0; i != boost::thread::hardware_concurrency(); ++i)
		{
			m_Threadpool.create_thread(boost::bind(&SG_ServerBase::WorkerThread, shared_from_this()));
		}
	}
	else
	{
		for (auto i = 0; i != iThreadcount; ++i)
		{
			m_Threadpool.create_thread(boost::bind(&SG_ServerBase::WorkerThread, shared_from_this()));
		}
	}
	StartServer();
	return true;
}

void SG_ServerBase::StartServer()
{
	m_Strand.post(boost::bind(&SG_ServerBase::Listen, shared_from_this()));
}

bool SG_ServerBase::isStopped()
{
	return (boost::interprocess::ipcdetail::atomic_cas32(&m_Shutdown, 1, 1) == 1);
}

bool SG_ServerBase::isError()
{
	return (boost::interprocess::ipcdetail::atomic_cas32(&m_ErrorState, 1, 1) == 1);
}

// ------------------------------------------------------------------ //

void SG_ServerBase::WorkerThread()
{
	while (1)
	{
		try
		{
			if (SG_ServerBase::isError() || SG_ServerBase::isStopped())
			{
				std::cout << "[" << __FUNCTION__ << "] Worker thread stopped." << std::endl;
				break;
			}

			boost::system::error_code ec;
			m_Service.run(ec);

			if (ec)
			{
				std::cout << "[" << __FUNCTION__ << "] Boost error. Errorcode: " << ec << std::endl;
				break;
			}
		}
		catch (std::exception &rException)
		{
			std::cout << "[" << __FUNCTION__ << "] Boost exception: " << rException.what() << std::endl;
			break;
		}
	}
}

void SG_ServerBase::Listen()
{
	boost::shared_ptr<SG_ClientSession> pSession(new SG_ClientSession(m_Service, m_Strand, shared_from_this()));
	m_Acceptor.async_accept(pSession->getSocket(), m_Strand.wrap(boost::bind(&SG_ServerBase::HandleConnect, shared_from_this(), pSession, boost::asio::placeholders::error)));
}

void SG_ServerBase::HandleConnect(const boost::shared_ptr<SG_ClientSession> pConnection, const boost::system::error_code &rEC)
{
	if (!rEC || !SG_ServerBase::isError() || !SG_ServerBase::isStopped())
	{
		pConnection->StartConnection();
	}
	else
	{
		std::cout << "[" << __FUNCTION__ << "] Failed to accept connection request." << std::endl;
		pConnection->DisconnectClient();
	}

	m_Strand.post(boost::bind(&SG_ServerBase::Listen, shared_from_this()));
}