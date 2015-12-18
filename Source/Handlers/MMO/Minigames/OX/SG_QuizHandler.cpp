#include "SG_QuizHandler.h"
#include <Packets/MMO/Minigames/MinigamePacketsResponse.h>

void SG_QuizHandler::EnterOX(const boost::shared_ptr<SG_ClientSession> Session)
{
	Session->m_Player->IsInOX = true;
	BM_SC_MMO_OX_ENTER_RESP response;
	BM_SC_MMO_OX_ENTER_RESP::initMessage<BM_SC_MMO_OX_ENTER_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_QuizHandler::LeaveOX(const boost::shared_ptr<SG_ClientSession> Session)
{
	Session->m_Player->IsInOX = false;
	BM_SC_MMO_OX_LEAVE_RESP response;
	BM_SC_MMO_OX_LEAVE_RESP::initMessage<BM_SC_MMO_OX_LEAVE_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

