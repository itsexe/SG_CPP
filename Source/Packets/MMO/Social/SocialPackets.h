#ifndef PACKETS_SOCIAL
#define PACKETS_SOCIAL
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
#include "Packets/PacketBaseMessage.h"

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
struct BM_SC_CHAT_MESSAGE : public TS_MESSAGE
{
	char sender[33];
	uint8_t type; // 0 = normal chat; 3 = whisper; 5 = shout
	uint16_t messagelength;
	char msg[70];
	static const uint16_t packetID = 2206;
};
struct BM_SC_CLAN_CREATION : public TS_MESSAGE
{
	char clanname[43];
	static const uint16_t packetID = 2344;
};
struct BM_SC_MATE_INFO : public TS_MESSAGE
{
	uint32_t uk1;
	char charname[43];
	static const uint16_t packetID = 2335;
};
struct BM_SC_UPDATE_MYMATEINFO : public TS_MESSAGE
{
	uint8_t age;
	uint32_t zoneid;
	char zoneinfo[121];
	char biostr[151];
	uint8_t isprivate; // 1 = private; 0 = public
	uint8_t gender; // 1 = Male; 2 = Female
	static const uint16_t packetID = 2262;
};
#endif