#ifndef SG_MMOHandler_H
#define SG_MMOHandler_H
#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include "Packets/MMO/MMOPackets.h"
#include <Packets/MMO/MMOPacketsResponse.h>

struct BM_SC_END_GAME;

class SG_MMOHandler
{
public:
	//Loginstuff
	static void EnterLobby(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet);
	static void SetSessionMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_SET_SESSION_MESSAGE* packet);

	//Gameinfo
	static void SendLevelInfo(const boost::shared_ptr<SG_ClientSession> Session);

	//Charlist
	static void SendCharList(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAR_LIST* packet);
	static void SelectChar(const boost::shared_ptr<SG_ClientSession> Session);

	//Charinfo
	static void SendTrickList(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendPlayerInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendCashBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendInventory(const boost::shared_ptr<SG_ClientSession> Session);

	//Charcreation
	static void CreateChar(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_CHAR* packet);

	//Multiplayer
	static void HandlePositionUpdate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MMO_GAME_MESSAGE* packet);

	//Channel
	static void SendChannellist(const boost::shared_ptr<SG_ClientSession> Session);
	static void EnterChannel(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_CHANNEL* packet);
	static void LeaveChannel(const boost::shared_ptr<SG_ClientSession> Session);

	//Quests
	static void SendMissionList(const boost::shared_ptr<SG_ClientSession> Session);
	static void CheckDailyCoins(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandleDailyCoins(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_QUEST_DAY_COIN* packet);
	static void StartMission(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendQuestList(const boost::shared_ptr<SG_ClientSession> Session);

	//Scipts and Debug
	static void UnlockDebugAccess(const boost::shared_ptr<SG_ClientSession> Session);
	static void RunClientSideScript(const boost::shared_ptr<SG_ClientSession> Session);


	static void EnterInventory(const boost::shared_ptr<SG_ClientSession> Session);
	static void LeaveInventory(const boost::shared_ptr<SG_ClientSession> Session);


	//UK
	static void SendPlayerDisguise(const boost::shared_ptr<SG_ClientSession> Session);
	static void BM_SC_MMO_COIN_ENTER(const boost::shared_ptr<SG_ClientSession> Session);
};

#endif