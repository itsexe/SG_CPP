#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Packets/MMO/MMOPackets.h"
#include "Networking/General/SG_ClientSession.h"

class SG_ChatHandler
{
public:
	static void HandleAdminCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
};

