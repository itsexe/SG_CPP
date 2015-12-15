#ifndef SG_MMOHandler_H
#define SG_MMOHandler_H
#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include "Packets/MMO/MMOPackets.h"

class SG_MMOHandler
{
public:



	//Loginstuff
	static void EnterLobby(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet);
	static void HandleCharCreation(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_CHAR* packet);
	static void SendCharList(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAR_LIST* packet);
	static void SelectChar(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendTrickList(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendPlayerInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendCashBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendLevelInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendInventory(const boost::shared_ptr<SG_ClientSession> Session);
	static void SetSessionMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_SET_SESSION_MESSAGE* packet);

	//Multiplayer
	static void HandlePositionUpdate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MMO_GAME_MESSAGE* packet);
	static void HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet);


	//Channel
	static void SendChannellist(const boost::shared_ptr<SG_ClientSession> Session);
	static void EnterChannel(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_CHANNEL* packet);
	static void LeaveChannel(const boost::shared_ptr<SG_ClientSession> Session);


	//Quests
	static void SendMissionList(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandleDailyCoins(const boost::shared_ptr<SG_ClientSession> Session);


	//Minigames
	static void StartMission(const boost::shared_ptr<SG_ClientSession> Session);
	static void EnterOX(const boost::shared_ptr<SG_ClientSession> Session);
	static void LeaveOX(const boost::shared_ptr<SG_ClientSession> Session);


	//Rooms
	static void SendRoomList(const boost::shared_ptr<SG_ClientSession> Session);
	static void RoomCreate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr, uint32_t id);
	static void RoomEnter(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_ROOM* packet);
	static void RoomLeave(const boost::shared_ptr<SG_ClientSession> Session);
	static void StartGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_START_GAME* packet);


	//Social stuff
	static void HandleMSN(const boost::shared_ptr<SG_ClientSession> Session);
	static void FindUser(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_MSN_FIND_USER* packet);
	static void FriendRequest(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_FRIEND_REQUEST* packet);

	//Scipts and Debug
	static void UnlockDebugAccess(const boost::shared_ptr<SG_ClientSession> Session);

};

#endif