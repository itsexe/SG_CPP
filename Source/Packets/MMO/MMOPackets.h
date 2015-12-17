#ifndef PACKETS_MMO
#define PACKETS_MMO

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
struct BM_SC_LOGIN : public TS_MESSAGE
{
	unsigned char sessionKey[33];
	static const uint16_t packetID = 2144;
};
struct BM_SC_CHAR_LIST : public TS_MESSAGE
{
	unsigned char sessionKey[33];
	static const uint16_t packetID = 2317;
};
struct BM_SC_SELECT_CHAR : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2066;
};
struct BM_SC_CREATE_CHAR : public TS_MESSAGE
{
	//This packet will be sent from the char creation
	uint8_t uk1;
	char charname[10];
	uint64_t uk2;
	uint64_t uk3;
	uint64_t uk4;
	uint32_t uk5;
	uint8_t uk6;
	uint8_t uk7;
	uint8_t uk8;
	uint8_t uk9;
	uint8_t uk10;
	uint8_t uk11;
	uint8_t uk12;
	uint8_t uk13;

	 //shirt
	uint8_t shirtid;
	uint16_t shirtuk1; //351 if shirtid is not 0
	uint8_t shirtuk2; // Always 0

	//short
	uint8_t shortid;
	uint16_t shortuk1; //351 if shortid is not 0
	uint8_t shortuk2; // Always 0

	static const uint16_t packetID = 2068;
};
struct BM_SC_PLAYER_INFO : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2313;
};
struct BM_SC_TRICK_LIST : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2104;
};
struct BM_SC_BALANCE_INFO : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2094;
};
struct BM_SC_CASH_BALANCE_INFO : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2271;
};
struct BM_SC_CHANNEL_LIST : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2005;
};
struct BM_SC_ENTER_CHANNEL : public TS_MESSAGE
{
	uint8_t channelid;
	static const uint16_t packetID = 2007;
};
struct BM_SC_LEAVE_CHANNEL : public TS_MESSAGE
{
	//Since we don't need this data, i just skip this
	static const uint16_t packetID = 2009;
};
struct BM_SC_MMO_GAME_MESSAGE : public TS_MESSAGE
{
	uint32_t uk1;
	uint16_t counter;
	uint32_t keystate;

	//coords
	float coord_x;
	float coord_y;
	float coord_angle_z;
	float coord_z;
	static const uint16_t packetID = 2017;
};
struct BM_SC_MMO_TICK_MESSAGE : public TS_MESSAGE
{
	//This packet is quiete useless, maybe we should disable it later.
	static const uint16_t packetID = 2019;
};
struct BM_SC_STATUS_MESSAGE : public TS_MESSAGE
{
	//This is some kind of update for the animations
	//TODO: Analyze what this packet is for
	static const uint16_t packetID = 2015;
};
struct BM_SC_MISSION_LIST : public TS_MESSAGE
{
	static const uint16_t packetID = 2072;
};
struct BM_SC_SET_SESSION_MESSAGE : public TS_MESSAGE
{
	uint8_t length;
	char message[14];
	static const uint16_t packetID = 2120;
};
struct BM_SC_CHAT_MESSAGE : public TS_MESSAGE
{
	char uk[30];
	uint16_t messagelength;
	char msg[70];
	static const uint16_t packetID = 2206;
};
struct ID_BZ_SC_ENTER_LOBBY : public TS_MESSAGE
{

	static const uint16_t packetID = 2275;
};
struct BM_SC_MMO_OX_ENTER: public TS_MESSAGE
{
	static const uint16_t packetID = 2030;
};
struct BM_SC_MMO_OX_LEAVE: public TS_MESSAGE
{
	static const uint16_t packetID = 2032;
};
struct BM_SC_START_MISSION: public TS_MESSAGE
{
	static const uint16_t packetID = 2074;
};
struct BM_SC_INVENTORY : public TS_MESSAGE
{
	static const uint16_t packetID = 2098;
};
struct BM_SC_GET_ROOMLIST : public TS_MESSAGE
{
	static const uint16_t packetID = 2303;
};
struct BM_SC_CREATE_ROOM : public TS_MESSAGE
{
	char Name[24];
	char password[4];
	char uk[48];
	uint8_t MaxPlayers;
	uint32_t Mode;
	uint8_t Level;
	static const uint16_t packetID = 2173;
};
struct BM_SC_ENTER_ROOM : public TS_MESSAGE
{
	uint8_t uk1;
	uint32_t roomid;
	static const uint16_t packetID = 2175;
};
struct BM_SC_LEAVE_ROOM : public TS_MESSAGE
{
	static const uint16_t packetID = 2177;
};
struct BM_SC_QUEST_DAY_COIN2 : public TS_MESSAGE
{
	static const uint16_t packetID = 2297;
};
struct MM_SC_MSN : public TS_MESSAGE
{
	//has some data
	static const uint16_t packetID = 5001;
};
struct MM_SC_MSN_FIND_USER : public TS_MESSAGE
{
	char username[42];
	static const uint16_t packetID = 5013;
};
struct MM_SC_FRIEND_REQUEST : public TS_MESSAGE
{
	char uk[40];
	char username[402];
	static const uint16_t packetID = 5015;
};
struct BM_SC_START_GAME : public TS_MESSAGE
{
	//has some data
	static const uint16_t packetID = 2189;
};
struct BM_SC_SELECT_MAP : public TS_MESSAGE
{
	uint16_t mapid;
	static const uint16_t packetID = 2198;
};
struct BM_SC_MINIGAME_START : public TS_MESSAGE
{
	uint8_t uk1;
	uint8_t uk2;
	uint8_t uk3;
	uint8_t uk4;
	char gameid[4];
	static const uint16_t packetID = 2048;
};
struct BM_SC_MINIGAME_FINISH : public TS_MESSAGE
{
	char gameid[30];
	static const uint16_t packetID = 2050;
};
struct BM_SC_UPDATE_ROUND : public TS_MESSAGE
{
	uint16_t uk1;
	static const uint16_t packetID = 2204;
};
struct BM_SC_FINISH_RACE : public TS_MESSAGE
{
	char gameid[16];
	static const uint16_t packetID = 2191;
};
#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
