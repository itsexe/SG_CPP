#include "SG_ChatHandler.h"
#include "Networking/General/SG_ServerBase.h"
#include <Packets/MMO/MMOPacketsResponse.h>
#include <Handlers/MMO/SG_MMOHandler.h>

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
		SG_MMOHandler::RoomEnter(Session,&pack, &Session->m_Server->Rooms_internal);
	}

}