#ifndef PACKETS_TS_CA_ACCOUNT_H
#define PACKETS_TS_CA_ACCOUNT_H

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

struct TS_CA_ACCOUNT_DES : public TS_MESSAGE
{
	char account[19];
	char password[32];
	static const uint16_t packetID = 1003;
};
struct TS_CA_VERSION : public TS_MESSAGE
{
	char szVersion[20];
	char szLang[3];
	static const uint16_t packetID = 1002;
};
struct TS_CA_SERVER_LIST : public TS_MESSAGE
{
	uint16_t uk1;
	uint8_t uk2;
	static const uint16_t packetID = 1004;
};
struct TS_CA_SELECT_SERVER : public TS_MESSAGE
{
	uint16_t xID;
	uint16_t Msg_ID;
	uint16_t Lobby_ID;
	uint16_t MMO_ID;
	static const uint16_t packetID = 1006;
};
#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
