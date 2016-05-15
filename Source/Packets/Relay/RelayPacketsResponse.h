#ifndef PACKETS_RELAY_RESPONSE
#define PACKETS_RELAY_RESPONSE

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)

#pragma pack(pop)
struct NM_SC_READY_GAME_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 6012;
};
struct NM_SC_START_GAME_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 6028;
	//static const uint16_t packetID = 6013;
};
struct NM_SC_START_GAME2_RESP : public TS_MESSAGE
{
	char successmessage[8];
	//static const uint16_t packetID = 6028;
	static const uint16_t packetID = 6013; 
};
struct NM_SC_EXPIRE_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 6019;
};
struct NM_SC_GET_SERVER_TICK_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 6029;
};
struct Playerinfo_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 6009;
};
#endif 