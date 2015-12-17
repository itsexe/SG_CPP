#ifndef SG_LobbyHandler_H
#define SG_LobbyHandler_H
#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "../../Networking/General/SG_ClientSession.h"
#include "../../Packets/MMO/MMOPackets.h"

class SG_LobbyHandler
{
public:
	static void HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet);
};

#endif