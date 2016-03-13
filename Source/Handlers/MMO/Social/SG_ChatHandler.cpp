#include "SG_ChatHandler.h"
#include "Networking/General/SG_ServerBase.h"
#include <Handlers/MMO/SG_MMOHandler.h>
#include <Tools/SG_Logger.h>
#include <Packets/MMO/Social/SocialPacketsResponse.h>
#include <Packets/MMO/Rooms/RoomPackets.h>
#include <Handlers/MMO/Rooms/SG_RoomHandler.h>
#include <Packets/MMO/Minigames/MinigamePacketsResponse.h>

void SG_ChatHandler::HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet)
{
	if (packet->msg[0] == 59)
	{
		SG_ChatHandler::HandleAdminCommand(Session, packet);
	}
	else
	{
		BM_SC_CHAT_MESSAGE_RESP response;
		BM_SC_CHAT_MESSAGE_RESP::initMessage<BM_SC_CHAT_MESSAGE_RESP>(&response);
		SG_Logger::instance().log(Session->m_Player->charname + ": " + std::string(packet->msg, packet->msg + packet->messagelength), SG_Logger::kLogLevelChat);
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
		response.successmessage[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
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
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
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
	if (msg == ";createbot")
	{
		std::cout << "Spawning bot...";
		BM_SC_PLAYER_CHAR_LIST_RESP response;
		BM_SC_PLAYER_CHAR_LIST_RESP::initMessage<BM_SC_PLAYER_CHAR_LIST_RESP>(&response);
		strcpy_s(response.resonse, static_cast<std::string>("SUCCESS").c_str());
		response.resonse[7] = static_cast<uint8_t>(0);
		response.uk1 = 1;
		response.uk2 = 1;
		response.uk3 = 1;
		response.uk4 = 1;
		response.uk5 = 1;

		std::string charname = "testuser";
		strcpy_s(response.charname, charname.c_str());
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
}