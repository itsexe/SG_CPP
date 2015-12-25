#ifndef PACKETS_SOCIAL_RESP
#define PACKETS_SOCIAL_RESP
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
struct BM_SC_CHAT_MESSAGE_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2207;
}; //Confirmation for sender
struct BM_SC_CHAT_MESSAGE_RESP2 : public TS_MESSAGE
{
	//not working atm
	char sender[33];
	unsigned short len;
	unsigned char type;
	char message[70];

	static const uint16_t packetID = 2208;
}; // Will be broadcasted players
struct MM_SC_MSN_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t uk3; //1
	uint32_t uk4; //1
	static const uint16_t packetID = 5002;
};
struct MM_SC_MSN_FIND_USER_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 5014;
};
struct MM_SC_FRIEND_REQUEST_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 5016;
};
struct BM_SC_CLAN_CREATION_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2345;
};
struct BM_SC_MATE_INFO_RESP : public TS_MESSAGE
{
	//here is most likely something wrong

	char successmessage[8];
	char uk1[25];
	uint8_t chartype;

	char charname[43];
	char uk2[74];
	char clantag[4];
	char clanname[87];
	uint8_t age;
	uint16_t level;
	uint16_t license;
	uint32_t zoneid;
	char zoneinfo[121];
	char biostr[218];

	static const uint16_t packetID = 2336;
};
#endif