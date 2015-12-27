#ifndef PACKETS_MINIGAMES_RESP
#define PACKETS_MINIGAMES_RESP
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct BM_SC_MINIGAME_START_RESP : public TS_MESSAGE
{
	//todo
	char successmessage[8];
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
struct BM_SC_MMO_OX_LEAVE_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2033;
};
#endif