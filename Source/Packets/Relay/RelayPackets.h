#ifndef PACKETS_TS_CA_ACCOUNT_H
#define PACKETS_TS_CA_ACCOUNT_H

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct NM_SC_KEEP_ALIVE : public TS_MESSAGE
{
	static const uint16_t packetID = 6000;
};


#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
