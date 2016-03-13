#include "SG_MinigameHandler.h"
#include <Packets/MMO/Minigames/MinigamePacketsResponse.h>


void SG_MinigameHandler::StartMinigame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MINIGAME_START* packet)
{
	BM_SC_MINIGAME_START_RESP response;
	BM_SC_MINIGAME_START_RESP::initMessage<BM_SC_MINIGAME_START_RESP>(&response);

	Session->SendPacketStruct(&response);
}

void SG_MinigameHandler::FinishMinigame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MINIGAME_FINISH* packet)
{
	BM_SC_MINIGAME_FINISH_RESP response;
	BM_SC_MINIGAME_FINISH_RESP::initMessage<BM_SC_MINIGAME_FINISH_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}