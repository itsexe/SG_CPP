#ifndef PACKETS_MMO
#define PACKETS_MMO

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct BM_SC_LOGIN : public TS_MESSAGE
{
	unsigned char sessionKey[33];
	static const uint16_t packetID = 2144;
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
#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
