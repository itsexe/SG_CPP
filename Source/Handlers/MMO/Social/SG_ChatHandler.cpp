#include "SG_ChatHandler.h"
#include "Networking/General/SG_ServerBase.h"
#include <Handlers/MMO/SG_MMOHandler.h>
#include <Tools/SG_Logger.h>
#include <Packets/MMO/Social/SocialPacketsResponse.h>
#include <Packets/MMO/Rooms/RoomPackets.h>
#include <Handlers/MMO/Rooms/SG_RoomHandler.h>

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
		SG_RoomHandler::RoomEnter(Session,&pack, &Session->m_Server->Rooms_internal);
	}

}

