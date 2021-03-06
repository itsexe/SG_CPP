#include "SG_ChatHandler.h"
#include "Networking/General/SG_ServerBase.h"
#include "Handlers/MMO/SG_MMOHandler.h"
#include "Tools/SG_Logger.h"
#include "Packets/MMO/Social/SocialPacketsResponse.h"
#include "Packets/MMO/Rooms/RoomPackets.h"
#include "Handlers/MMO/Rooms/SG_RoomHandler.h"
#include "Packets/MMO/Minigames/MinigamePacketsResponse.h"
#include "Handlers/Relay/SG_RelayHandler.h"
#include "Packets/MMO/MMOPackets.h"
#include <boost/algorithm/string.hpp>
#include "Tools/SG_DataConverter.h"

void SG_ChatHandler::HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet)
{
	if (packet->msg[0] == 59)
	{
		SG_ChatHandler::HandleAdminCommand(Session, packet);
	}
	else if(packet->msg[0] == '/')
	{
		SG_ChatHandler::HandleUserCommand(Session, packet);
	}
	else
	{
		/*
		// Uncommenting this will show the bubble on the top on the character head, but will display the message twice on chat...
		BM_SC_CHAT_MESSAGE_RESP response;
		BM_SC_CHAT_MESSAGE_RESP::initMessage<BM_SC_CHAT_MESSAGE_RESP>(&response);
		SG_Logger::instance().log(Session->m_Player->charname + ": " + std::string(packet->msg, packet->msg + packet->messagelength), SG_Logger::kLogLevelChat);
		memcpy(response.successmessage, "SUCCESS",8);
		response.successmessage[7] = static_cast<uint8_t>(0);

		Session->SendPacketStruct(&response);
		*/

		std::cout << sizeof(packet->msg) << std::endl;
		
		BM_SC_CHAT_MESSAGE_RESP2 response;
		BM_SC_CHAT_MESSAGE_RESP2::initMessage<BM_SC_CHAT_MESSAGE_RESP2>(&response);

		char message[68];
		for(int i = 0; i < 69 ; i ++)
		{
			if(packet->msg[i] != '0')
			{
				message[i] = packet->msg[i];
			}
			message[i] = '0';
		}
		
		memcpy(response.sender, static_cast<std::string>(packet->sender).c_str(),32);
		memcpy(response.message, static_cast<std::string>(message).c_str(),70);
		response.type = CHAT_NORMAL2;
		Session->m_Server->SendBroadcast(&response);

	}
}

void SG_ChatHandler::HandleAdminCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet)
{

	std::string msg(packet->msg, packet->messagelength);
	if (msg == ";flushrooms")
	{
		Session->m_Server->Rooms_internal.clear();
	}
	if (msg == ";finishrace")
	{
		BM_SC_END_GAME response;
		BM_SC_END_GAME::initMessage<BM_SC_END_GAME>(&response);
		memcpy(response.successmessage, "SUCCESS", 8);
		response.successmessage[7] = static_cast<uint8_t>(0);
		Session->m_Server->SendRoomBroadcast(&response, Session->m_Player->roomptr->RoomID, Session, true);

		BM_SC_ENTER_ROOM pack;
		BM_SC_ENTER_ROOM::initMessage<BM_SC_ENTER_ROOM>(&pack);
		SG_RoomHandler::RoomEnter(Session, &pack, &Session->m_Server->Rooms_internal);
	}
	if (msg == ";disconnect")
	{
		Session->DisconnectClient();
	}
	if (strncmp(";setrank", msg.c_str(), strlen(";setrank") - 1) == 0)
	{
		msg = msg.substr(9);
		std::cout << "Set Rank from " << Session->m_Player->charname << "[" << Session->m_Player->playerid << "] to " << msg.c_str() << std::endl;
		Session->m_Player->rank = atoi(msg.c_str());
		Session->m_Server->SaveChar(Session);
	}
	if (strncmp(";setrupees", msg.c_str(), strlen(";setrupees") - 1) == 0)
	{
		msg = msg.substr(11);
		std::cout << "Set Rupees from " << Session->m_Player->charname << "[" << Session->m_Player->playerid << "] to " << msg.c_str() << std::endl;
		Session->m_Player->rupees = atoi(msg.c_str());
		Session->m_Server->SaveChar(Session);
	}
	if (strncmp(";setcoins", msg.c_str(), strlen(";setcoins") - 1) == 0)
	{
		msg = msg.substr(10);
		std::cout << "Set Coins from " << Session->m_Player->charname << "[" << Session->m_Player->playerid << "] to " << msg.c_str() << std::endl;
		Session->m_Player->coins = atoi(msg.c_str());
		Session->m_Server->SaveChar(Session);
	}
	if (strncmp(";setname", msg.c_str(), strlen(";setname") - 1) == 0)
	{
		msg = msg.substr(9);
		std::cout << "Set Name from " << Session->m_Player->charname << "[" << Session->m_Player->playerid << "] to " << msg.c_str() << std::endl;
		Session->m_Player->charname = msg.c_str();
		Session->m_Server->SaveChar(Session);
	}
	if (strncmp(";announce", msg.c_str(), strlen(";announce") - 1) == 0)
	{
		msg = msg.substr(10);

		BM_SC_CHAT_MESSAGE_RESP2 response;
		BM_SC_CHAT_MESSAGE_RESP2::initMessage<BM_SC_CHAT_MESSAGE_RESP2>(&response);

		memcpy(response.sender, static_cast<std::string>("SG").c_str(),32);
		memcpy(response.message, static_cast<std::string>(msg).c_str(),70);
		response.type = CHAT_SYSTEM_ANNOUNCEMENT;
		Session->m_Server->SendBroadcast(&response);
	}
	if (msg == ";createbot")
	{
		std::cout << "Spawning bot...";
		BM_SC_PLAYER_CHAR_LIST_RESP response;
		BM_SC_PLAYER_CHAR_LIST_RESP::initMessage<BM_SC_PLAYER_CHAR_LIST_RESP>(&response);
		memcpy(response.resonse, "SUCCESS", 8);
		response.resonse[7] = static_cast<uint8_t>(0);
		response.uk1 = 1;
		response.uk2 = 1;
		response.uk3 = 1;
		response.uk4 = 1;
		response.uk5 = 1;

		std::string charname = "testuser";
		memcpy(response.charname, charname.c_str(),43);
		for (auto i = Session->m_Player->charname.length(); i != 43; i++)
		{
			response.charname[i] = static_cast<uint8_t>(0);
		}
		response.firstlogin = 1; //0 will push the Player to the Charcreation
		response.chartype = 4;
		Session->SendPacketStruct(&response);
	}
	if (msg == ";selectquiz")
	{	
		BM_SC_MMO_OX_SELECT_RESP response;
		BM_SC_MMO_OX_SELECT_RESP::initMessage<BM_SC_MMO_OX_SELECT_RESP>(&response);
		response.uk1 = 1;
		Session->SendPacketStruct(&response);
	}
	if (msg == ";startquizall")
	{
		BM_SC_MMO_OX_START_ALL_RESP response;
		BM_SC_MMO_OX_START_ALL_RESP::initMessage<BM_SC_MMO_OX_START_ALL_RESP>(&response);
		//response. = 1;
		Session->SendPacketStruct(&response);
	}
	if (msg == ";quiznotice")
	{
		BM_SC_MMO_OX_NOTICE_RESP response;
		BM_SC_MMO_OX_NOTICE_RESP::initMessage<BM_SC_MMO_OX_NOTICE_RESP>(&response);
		//response. = 1;
		Session->SendPacketStruct(&response);
	}
	if (msg == ";pausequiz")
	{
		BM_SC_MMO_OX_PAUSE_RESP response;
		BM_SC_MMO_OX_PAUSE_RESP::initMessage<BM_SC_MMO_OX_PAUSE_RESP>(&response);
		//response. = 1;
		Session->SendPacketStruct(&response);
	}
	if (msg == ";disconnect")
	{
		Session->DisconnectClient();
	}
	if (msg == ";clearRooms")
	{
		SG_RoomHandler::RemoveAllRooms(Session);
	}
	if (msg == ";spawnCoin")
	{
		SG_MMOHandler::BM_SC_MMO_COIN_ENTER(Session);
		std::cout << "BM_SC_MMO_COIN_ENTER" << std::endl;
	}
	if (msg == ";go")
	{
		//SG_RelayHandler::StartGame(Session);
		std::cout << "GOOGOGOGOGOGOGOGO" << std::endl;
#ifdef _WIN32
		Sleep(2000);
#endif

		for(int i = 0;i < 100000;i++)
		{
			BULLSHIT_TEST rep;
			rep.id = i;
			BULLSHIT_TEST::initMessage(&rep);
			std::cout << i << std::endl;
			Session->m_Server->SendBroadcast(&rep);
		}
	}
	
	if (msg == ";go2")
	{
		SG_RelayHandler::StartGame2(Session);
		std::cout << "GOOGOGOGOGOGOGOGO" << std::endl;
	}

	// Chat test.
	if (msg == ";b")
	{
		for(char i = 0;i<254;i++)
		{
#ifdef _WIN32
			Sleep(100);
#endif
			std::cout << i << std::endl;
			BM_SC_CHAT_MESSAGE_RESP2  response;
			BM_SC_CHAT_MESSAGE_RESP2::initMessage<BM_SC_CHAT_MESSAGE_RESP2>(&response);

			char mg[30];
			SG_Logger::instance().log(Session->m_Player->charname + ": " + std::string(packet->msg, packet->msg + packet->messagelength), SG_Logger::kLogLevelChat);
			
			memcpy(response.sender, static_cast<std::string>(packet->sender).c_str(), 32);
			memcpy(response.message, static_cast<std::string>(mg).c_str(), 30);
			response.id = i;
			Session->m_Server->SendBroadcast(&response);

			std::cout << response.id << std::endl;
		}
	}
}

void SG_ChatHandler::HandleUserCommand(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet)
{
	std::vector<std::string> strs;
	boost::split(strs, packet->msg, boost::is_any_of(" "));

	if(!strcmp(strs[0].c_str(), "/w"))
	{		
	}
}