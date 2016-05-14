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

	char uk;

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
struct ID_BZ_SC_ENTER_LOBBY : public TS_MESSAGE
{

	static const uint16_t packetID = 2275;
};

struct BM_SC_START_MISSION: public TS_MESSAGE
{
	//TODO 
	static const uint16_t packetID = 2074;
	// There is an array of chars (maybe a list of id, or a string)
};
struct BM_SC_INVENTORY : public TS_MESSAGE
{
	static const uint16_t packetID = 2098;
};

struct BM_SC_QUEST_DAY_COIN2 : public TS_MESSAGE
{
	static const uint16_t packetID = 2297;
};


struct BM_SC_QUEST_DAY_COIN : public TS_MESSAGE
{
	uint16_t uk1;
	static const uint16_t packetID = 2295;
};
struct BM_SC_CHARACTER_INFO : public TS_MESSAGE
{
	char charname[40];
	static const uint16_t packetID = 2146;
};
struct BM_SC_ENTER_INVENTORY : public TS_MESSAGE
{
	static const uint16_t packetID = 2078;
};
 struct BM_SC_LEAVE_INVENTORY : public TS_MESSAGE
 {
	 static const uint16_t packetID = 2080;
 };
 struct BM_SC_QUEST_LIST : public TS_MESSAGE
 {
	 static const uint16_t packetID = 2106;
 };
 struct BM_SC_PLAYER_DISGUISE : public TS_MESSAGE
 {
	 static const uint16_t packetID = 2340;
 };

 struct BULLSHIT_TEST : public TS_MESSAGE
 {
	 static const uint16_t packetID = 1234;
 };

#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
