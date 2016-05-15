#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include <Packets/MMO/Social/SocialPackets.h>

class SG_ChatHandler
{
public:
	typedef enum
	{
		CHAT_SYSTEM_INFO = 99,
		CHAT_NORMAL = 3,
		CHAT_ALL = 5,
		CHAT_SYSTEM_ANNOUNCEMENT = 10,
		CHAT_WHISP_IN = 20,
		CHAT_WHISP_OUT = 21,
		CHAT_DEBUG = 100
	} CHAT_TYPE;

	static void HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
	static void HandleAdminCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
	static void HandleUserCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
};

