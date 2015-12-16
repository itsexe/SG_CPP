#ifndef PACKETS_RELAY_H
#define PACKETS_RELAY_H

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct NM_SC_KEEP_ALIVE : public TS_MESSAGE
{
	static const uint16_t packetID = 6000;
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
#pragma pack(pop)

#endif
