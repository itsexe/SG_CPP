#ifndef PACKETS_MINIGAMES
#define PACKETS_MINIGAMES
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
struct BM_SC_MMO_OX_ENTER : public TS_MESSAGE
{
	static const uint16_t packetID = 2030;
};
struct BM_SC_MMO_OX_LEAVE : public TS_MESSAGE
{
	static const uint16_t packetID = 2032;
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
#endif