#ifndef PACKETS_MMO
#define PACKETS_MMO

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct BM_SC_LOGIN : public TS_MESSAGE
{
	unsigned char sessionKey[33];
	static const uint16_t packetID = 2144;
};

#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
