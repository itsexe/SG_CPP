#pragma once
#include <Packets/PacketBaseMessage.h>

struct BM_SC_GET_ROOMLIST : public TS_MESSAGE
{
	static const uint16_t packetID = 2303;
};
struct BM_SC_CREATE_ROOM : public TS_MESSAGE
{
	char Name[24];
	char password[4];
	char uk[48];
	uint8_t MaxPlayers;
	uint32_t Mode;
	uint8_t Level;
	static const uint16_t packetID = 2173;
};
struct BM_SC_ENTER_ROOM : public TS_MESSAGE
{
	uint8_t uk1;
	uint32_t roomid;
	static const uint16_t packetID = 2175;
};
struct BM_SC_READY_GAME : public TS_MESSAGE
{
	static const uint16_t packetID = 2187;
};
struct BM_SC_LEAVE_ROOM : public TS_MESSAGE
{
	static const uint16_t packetID = 2177;
};
struct BM_SC_START_GAME : public TS_MESSAGE
{
	//has some data
	static const uint16_t packetID = 2189;
};
struct BM_SC_SELECT_MAP : public TS_MESSAGE
{
	uint16_t mapid;
	static const uint16_t packetID = 2198;
};
struct BM_SC_UPDATE_ROUND : public TS_MESSAGE
{
	uint16_t uk1;
	static const uint16_t packetID = 2204;
};
struct BM_SC_FINISH_RACE : public TS_MESSAGE
{
	char gameid[16];
	static const uint16_t packetID = 2191;
};
struct BM_SC_UNKNOWN_INFO : public TS_MESSAGE
{
	uint8_t uk1;
	uint32_t id;
	static const uint16_t packetID = 2183;
};
struct BM_SC_CHARACTER_INFO_RESP : public TS_MESSAGE
{


	char successmessage[8];
	uint32_t uk1;
	uint32_t uk2;
	uint32_t uk3;
	uint32_t uk4;
	char charname[40];
	uint32_t uk5;
	uint32_t uk6;
	uint8_t uk7;
	uint8_t chartype;
	uint8_t uk8;
	uint32_t uk9;
	uint32_t uk10;
	uint32_t uk11;
	uint32_t uk12;
	uint32_t uk13;
	uint32_t uk14;
	uint32_t uk15;
	uint32_t uk16;
	uint32_t charlevel;
	uint32_t uk17;
	uint32_t uk18;
	uint32_t uk19;
	uint32_t uk20;
	uint32_t uk21;
	uint32_t head;
	uint32_t face;
	uint32_t upper;
	uint32_t lower;
	uint32_t foot;
	uint32_t hand;
	uint32_t google;
	uint32_t accesoire;
	uint32_t theme;
	uint32_t mantle;
	uint32_t buckle;
	uint32_t vent;
	uint32_t nitro;
	uint32_t wheels;
	uint8_t uk22;
	uint32_t uk23;
	uint32_t tricksize;
	sg_constructor::Tricksrace tricklist[13];

	static const uint16_t packetID = 2147;
};