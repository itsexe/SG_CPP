#ifndef SG_LobbyServer_H
#define SG_LobbyServer_H
#pragma once
#include <vector>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Networking/General/SG_ServerBase.h"
#include "Networking/General/SG_ClientSession.h"
class SG_LobbyServer : public SG_ServerBase
{

private:
	bool OnClientConnected(const boost::shared_ptr<SG_ClientSession> Session);
	void OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> Session);
	bool OnPacketReceived(const boost::shared_ptr<SG_ClientSession> Session, const TS_MESSAGE* packet);
};
#endif