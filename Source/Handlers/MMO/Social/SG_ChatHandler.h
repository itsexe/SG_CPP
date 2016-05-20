#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include <Packets/MMO/Social/SocialPackets.h>

class SG_ChatHandler
{
public:
	typedef enum
	{
		CHAT_NORMAL = 1,				// normal, white chat
		CHAT_NORMAL2 = 2,				// same
		CHAT_ALL = 3,					// orange message
		CHAT_MP = 5,					// same
		CHAT_SYSTEM_ANNOUNCEMENT = 10,	// red, caps lock, center of the screen
		CHAT_WHISP_OUT = 11,			// yellow, like system messages
		CHAT_GM = 20,					// pink
		CHAT_CLAN = 21,					// purple
		CHAT_SYSTEM_INFO = 99,			// yellow, like system messages
		CHAT_DEBUG = 100				// red
	} CHAT_TYPE;

	static void HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
	static void HandleAdminCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
	static void HandleUserCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);
};

