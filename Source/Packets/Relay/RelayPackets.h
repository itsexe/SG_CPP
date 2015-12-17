#ifndef PACKETS_RELAY_H
#define PACKETS_RELAY_H

#include "../../Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct NM_SC_KEEP_ALIVE : public TS_MESSAGE
{
	static const uint16_t packetID = 6000;
};
struct NM_SC_KEEP_ALIVE_INGAME : public TS_MESSAGE
{
	static const uint16_t packetID = 6026;
};
struct NM_SC_LOGIN : public TS_MESSAGE
{
	uint8_t status;
	char uk[40];
	static const uint16_t packetID = 6001;
};
struct NM_SC_EXPIRE : public TS_MESSAGE
{
	static const uint16_t packetID = 6018;
};
struct Playerinfo : public TS_MESSAGE
{
	char uk1[80];
	static const uint16_t packetID = 6008;
};
#pragma pack(pop)

#endif
