#pragma once
#include <Networking/General/SG_ClientSession.h>
#include <Packets/MMO/Rooms/RoomPackets.h>
#include <Packets/MMO/Rooms/RoomPacketsResponse.h>
#include <Packets/MMO/MMOPackets.h>

class SG_RoomHandler
{
public:
	static void SendRoomList(const boost::shared_ptr<SG_ClientSession> Session, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr);
	static void RoomCreate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr, uint32_t id);
	static void RoomEnter(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr);
	static void RoomLeave(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandlePlayerReady(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandlePlayerRoomInfo(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHARACTER_INFO* packet);
	static void StartGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_START_GAME* packet);
	static void EndGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_FINISH_RACE* packet);
	static void SelectMap(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_SELECT_MAP* packet);
	static void UpdateMap(const boost::shared_ptr<SG_ClientSession> Session);
	static void HandleUnknownInfo(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_UNKNOWN_INFO* packet);
	static BM_SC_ROOM_MULTI_INFO_RESP &GeneratePlayerRoomUpdate(const boost::shared_ptr<SG_ClientSession> Session, uint8_t position, bool newplayer = false);
};

