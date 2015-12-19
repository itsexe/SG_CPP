#ifndef PACKETS_ROOMS_RESP
#define PACKETS_ROOMS_RESP
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
#include <Constructors/sg_constructor.h>

struct BM_SC_GET_ROOMLIST_RESP : public TS_MESSAGE_WNA
{
	uint16_t roomcount;
	uint16_t uk1;
	uint16_t uk2;
	sg_constructor::rooms_packet rooms[0];
	//std::vector<sg_constructor::rooms_packet> rooms;
	static const uint16_t packetID = 2304;
};
struct BM_SC_CREATE_ROOM_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t roomid;
	char relayip[20]; //Yes, this is 20 for whatever reason
	uint16_t relayport;
	uint8_t team; // 1 = red | 2 = Blue
	uint8_t uk3;
	uint8_t uk4;
	uint32_t udpport; //default 5000
	static const uint16_t packetID = 2174;
};
struct BM_SC_CREATE_FAILED_RESP : public TS_MESSAGE
{
	char errormessage[16];
	static const uint16_t packetID = 2174;
};
struct BM_SC_CREATE_ROOM_ALREADYJOINED_RESP : public TS_MESSAGE
{
	char errormessage[21];
	static const uint16_t packetID = 2174;
};
struct BM_SC_ENTER_ROOM_SUCCESS_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	char relayip[20];
	uint16_t relayport;
	uint8_t team; // 1 = red | 2 = Blue
	uint8_t uk3;
	uint8_t uk4;
	uint32_t udpport; //default 5000
	static const uint16_t packetID = 2176;
};
struct BM_SC_ENTER_ROOM_FAILED_RESP : public TS_MESSAGE
{
	char errormessage[16];
	static const uint16_t packetID = 2176;
};
struct BM_SC_ENTER_ROOM_ALREADYJOINED_RESP : public TS_MESSAGE
{
	char errormessage[21];
	static const uint16_t packetID = 2176;
};
struct BM_SC_LEAVE_ROOM_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2178;
};
struct BM_SC_ROOM_MULTI_INFO_RESP : public TS_MESSAGE
{
	char remoteendpoint[33];
	char charname[40];
	uint8_t lobbyposition;
	uint8_t chartype;
	uint8_t enterinfo; //has to be 3 BM_SC_USER_INFO:USER_ENTER
	uint8_t isadmin;
	uint8_t slotdisplay;
	uint8_t ready;
	uint8_t status;
	uint16_t uk1;
	uint8_t uk2;
	uint8_t uk3;
	static const uint16_t packetID = 2165;
};
struct BM_SC_SELECT_MAP_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint16_t mapid;
	static const uint16_t packetID = 2199;
};
struct BM_SC_MAP_INFO_RESP : public TS_MESSAGE
{
	uint16_t mapid;
	static const uint16_t packetID = 2164;
};
struct BM_SC_START_GAME_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	char encryptionkey[16];
	uint16_t playercount;

	//Playerlist
	sg_constructor::room_players players[2];
	static const uint16_t packetID = 2190;
};
struct BM_SC_END_GAME : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2192;
};
struct BM_SC_UNKNOWN_INFO_RESP : public TS_MESSAGE
{
	char name[40];
	static const uint16_t packetID = 2184;
};
struct BM_SC_READY_GAME_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2188;
};
#endif