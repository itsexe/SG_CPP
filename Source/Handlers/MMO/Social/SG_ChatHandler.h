#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include <Packets/MMO/Social/SocialPackets.h>

class SG_ChatHandler
{
public:
	static void HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
	static void HandleAdminCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
};

