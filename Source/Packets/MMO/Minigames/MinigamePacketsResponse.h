#ifndef PACKETS_MINIGAMES_RESP
#define PACKETS_MINIGAMES_RESP
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct BM_SC_MINIGAME_START_RESP : public TS_MESSAGE
{
	//todo
	uint32_t uk1;
	uint32_t uk2;
	int uk3;
	uint32_t uk4;

	static const uint16_t packetID = 2049;
};
struct BM_SC_MINIGAME_FINISH_RESP : public TS_MESSAGE
{
	//todo
	char successmessage[8];
	static const uint16_t packetID = 2051;
};
struct BM_SC_MMO_OX_ENTER_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2031;
};
struct BM_SC_MMO_OX_PAUSE_RESP : public TS_MESSAGE
{
	static const uint16_t packetID = 2045;
};
struct BM_SC_MMO_OX_REGISTER_RESP : public TS_MESSAGE
{
	char successmessage[8];
	int uk;
	static const uint16_t packetID = 2041;
};
struct BM_SC_MMO_OX_REGISTER_ALL : public TS_MESSAGE
{
	static const uint16_t packetID = 2044;
};
struct BM_SC_MMO_OX_START_ALL_RESP : public TS_MESSAGE
{
	static const uint16_t packetID = 2042;
};
struct BM_SC_MMO_OX_SELECT_RESP : public TS_MESSAGE
{
	uint32_t uk1;
	static const uint16_t packetID = 2036;
};

struct BM_SC_MMO_OX_LEAVE_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2033;
};
struct BM_SC_MMO_OX_NOTICE_RESP : public TS_MESSAGE
{
	static const uint16_t packetID = 2039;
};
#endif