#ifndef PACKETS_MMO_RESPONSE
#define PACKETS_MMO_RESPONSE

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
struct BM_SC_LOGIN_RESP : public TS_MESSAGE
{
	unsigned char resonse[8] = "SUCCESS";
	static const uint16_t packetID = 2144;
};
#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
