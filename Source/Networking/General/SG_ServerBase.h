#ifndef SERVERBASE
#define SERVERBASE
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "SG_ClientSession.h"
#include "Packets/PacketBaseMessage.h"

/*++
Class for setting up the server and checking for incoming connections.
--*/

class SG_ClientSession;

class SG_ServerBase : public boost::enable_shared_from_this<SG_ServerBase>
{

public:
	SG_ServerBase();
	virtual ~SG_ServerBase();

	// if Threadcount is 0 it uses max thread count
	bool InitServer(const std::string &IP, uint32_t Port, int32_t Threadcount);
	void StartServer();

	bool isStopped();
	bool isError();
	std::list<boost::shared_ptr<SG_ClientSession> > Sessions;
	std::list<boost::shared_ptr<sg_constructor::Room> > Rooms_internal;
	std::list<boost::shared_ptr<sg_constructor::rooms_packet> > Rooms_packet;

	uint32_t lastroomid;
	void SendBroadcast(const TS_MESSAGE* packet);
	void SendRoomBroadcast(const TS_MESSAGE* packet, uint32_t roomid, const boost::shared_ptr<SG_ClientSession> sender, bool sendtosender = false);
	uint8_t GetPlayersInRoom(uint32_t roomid);
	void SaveChar(const boost::shared_ptr<SG_ClientSession> Session);

	std::vector<int> idConnected; // Array with connected account IDs
	std::vector<int> nbConnected; // Array needed to store "how many DC has been proc'd" -> 2 DC when user logs out.

private:
	void WorkerThread();
	void Listen();
	void HandleConnect(const boost::shared_ptr<SG_ClientSession> Connection, const boost::system::error_code &Errorcode);

	boost::asio::io_service m_Service;
	boost::asio::ip::tcp::acceptor m_Acceptor;
	boost::thread_group m_Threadpool;
	boost::asio::strand m_Strand;

	volatile uint32_t m_Shutdown;
	volatile uint32_t m_ErrorState;

public:
	virtual bool OnClientConnected(const boost::shared_ptr<SG_ClientSession> connection) = 0;
	virtual void OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> connection) = 0;
	virtual bool OnPacketReceived(const boost::shared_ptr<SG_ClientSession> connection, const TS_MESSAGE* packet) = 0;

};


#endif