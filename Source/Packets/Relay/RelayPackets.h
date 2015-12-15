#ifndef PACKETS_TS_CA_ACCOUNT_H
#define PACKETS_TS_CA_ACCOUNT_H

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct NM_SC_KEEP_ALIVE : public TS_MESSAGE
{
	static const uint16_t packetID = 6000;
};
struct NM_SC_LOGIN : public TS_MESSAGE
{
	uint8_t status;
	static const uint16_t packetID = 6001;
};

#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
