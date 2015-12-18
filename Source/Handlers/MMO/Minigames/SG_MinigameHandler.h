#pragma once
#include <Packets/MMO/Minigames/MinigamePackets.h>
#include <Networking/General/SG_ClientSession.h>

class SG_MinigameHandler
{
public:
	static void StartMinigame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MINIGAME_START* packet);
	static void FinishMinigame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MINIGAME_FINISH* packet);
};

