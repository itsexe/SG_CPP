#ifndef PACKETS_MMO_RESPONSE
#define PACKETS_MMO_RESPONSE
#include <cstdint>
#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
#include "Constructors/sg_constructor.h"

struct BM_SC_LOGIN_RESP : public TS_MESSAGE
{
	char resonse[8];
	static const uint16_t packetID = 2144;
};
struct BM_SC_LOGIN_RESP_FAILURE : public TS_MESSAGE
{
	char resonse[16];
	static const uint16_t packetID = 2144;
};
struct BM_SC_PLAYER_CHAR_LIST_RESP : public TS_MESSAGE
{
	char resonse[8]; // SUCCESS
	uint64_t uk1;
	uint64_t uk2;
	uint8_t uk3;
	char charname[43]; // Charname, you can use some html code like: <#ff0000> and <glow>
	uint16_t firstlogin;
	uint32_t uk4; 
	uint32_t chartype;
	uint32_t uk5;
	static const uint16_t packetID = 2318;
};
struct BM_SC_SELECT_CHAR_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2067;
};
struct BM_SC_PLAYER_INFO_RESP : public TS_MESSAGE
{
	uint32_t uk1; //needs to be 4
	uint16_t size1; // size of initpacket 1
	char successmessage[8];
	
	uint32_t uk2;
	uint32_t uk3;
	uint32_t uk4;
	uint32_t uk5;
	uint32_t uk6;
	uint16_t uk7;
	uint32_t uk8 = 5;

	//Subpacket 1
	uint16_t sp1id = 1;
	uint16_t sp1size = 50;
	char mapname1[12];
	uint8_t uk9;
	uint32_t uk10;
	uint32_t uk11;
	uint32_t uk12;
	uint32_t uk13;
	uint32_t uk14;
	uint32_t uk15;
	uint32_t uk16;
	char mapname2[9];

	//Subpacket 2
	uint16_t sp2id;
	uint16_t sp2size;
	uint16_t uk17;
	uint16_t uk18;
	uint64_t level;

	//Subpacket 4
	uint16_t sp4id;
	uint16_t sp4size;
	uint32_t uk19;
	uint32_t uk20;
	uint32_t uk31; 

	//Subpacket 64
	uint16_t sp64id;
	uint16_t sp64size;
	uint32_t uk32;
	uint32_t uk33;
	uint32_t uk34;
	uint32_t uk35;

	//Subpacket 512
	uint16_t sp512id;
	uint16_t sp512size;
	float speed;
	float accel;
	float turn;
	float brake;
	float boostspeed;
	float overspeed;
	float boosterc;
	float trick;
	float uk36;
	float uk37;

	//Subpacket 1024
	uint16_t sp1024id;
	uint16_t sp1024size;
	uint32_t count1;
	uint32_t count2;
	uint32_t count3;
	uint32_t count4;

	static const uint16_t packetID = 2314;
};
struct BM_SC_TRICK_LIST_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint8_t uk3;
	uint16_t trickcount; //13	ad
	//sg_constructor::Trickconstructor tricklist[13];

	uint32_t TrickIDGrind;
	uint32_t TricklvlGrind;
	uint8_t ApplyTrickGrind;

	uint32_t TrickIDBackFlip;
	uint32_t TricklvlBackFlip;
	uint8_t ApplyTrickBackFlip;

	uint32_t TrickIDFrontFlip;
	uint32_t TricklvlFrontFlip;
	uint8_t ApplyTrickFrontFlip;

	uint32_t TrickIDAirTwist;
	uint32_t TricklvlAirTwist;
	uint8_t ApplyTrickAirTwist;

	uint32_t TrickIDPowerSwing;
	uint32_t TricklvlPowerSwing;
	uint8_t ApplyTrickPowerSwing;

	uint32_t TrickIDGripTurn;
	uint32_t TricklvlGripTurn;
	uint8_t ApplyTrickGripTurn;

	uint32_t TrickIDDash;
	uint32_t TricklvlDash;
	uint8_t ApplyTrickDash;

	uint32_t TrickIDBackSkating;
	uint32_t TricklvlBackSkating;
	uint8_t ApplyTrickBackSkating;

	uint32_t TrickIDJumpingSteer;
	uint32_t TricklvlJumpingSteer;
	uint8_t ApplyTrickJumpingSteer;

	uint32_t TrickIDButting;
	uint32_t TricklvlButting;
	uint8_t ApplyTrickButting;

	uint32_t TrickIDPowerSlide;
	uint32_t TricklvlPowerSlide;
	uint8_t ApplyTrickPowerSlide;

	uint32_t TrickIDPowerJump;
	uint32_t TricklvlPowerJump;
	uint8_t ApplyTrickPowerJump;

	uint32_t TrickIDWallRide;
	uint32_t TricklvlWallRide;
	uint8_t ApplyTrickWallRide;


	static const uint16_t packetID = 2105;
};
struct BM_SC_BALANCE_INFO_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t rupees;
	uint32_t coin;
	uint32_t gpotatos;
	uint32_t questpoints;
	static const uint16_t packetID = 2095;
};
struct BM_SC_CHANNEL_LIST_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint16_t channelcount;
	uint8_t channelid;
	char channelname[12];
	uint32_t uk3 = 5;
	uint32_t uk4 = 6;
	uint32_t uk5 = 7;
	uint32_t currentplayers = 15;
	uint32_t maximumplayers = 1337;
	static const uint16_t packetID = 2006;
};
struct BM_SC_ENTER_CHANNEL_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint8_t uk3;
	uint16_t uk4;
	static const uint16_t packetID = 2008;
};
struct BM_SC_LEAVE_CHANNEL_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t uk3;
	static const uint16_t packetID = 2010;
};
struct ID_BZ_SC_ENTER_LOBBY_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t uk3;
	static const uint16_t packetID = 19019;
};
struct BM_SC_SET_SESSION_MESSAGE_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint16_t length;
	char sessionmessage[21];
	static const uint16_t packetID = 2119;
};
struct BM_SC_CREATE_CHAR_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2069;
};
struct BM_SC_MISSION_LIST_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint16_t count;
	uint8_t uk3; //must be "1"
	std::vector<uint64_t> missions;
	static const uint16_t packetID = 2073;
};
struct BM_SC_START_MISSION_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t missionid;
	static const uint16_t packetID = 2075;
};
struct BM_SC_INVENTORY_RESP : public TS_MESSAGE_WNA
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint8_t uk3;
	uint16_t count;
	sg_constructor::Item items[];
	static const uint16_t packetID = 2099;
};
struct BM_SC_CASH_BALANCE_INFO_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t coin;
	static const uint16_t packetID = 2272;
};
struct BM_SC_LEVEL_INFO_RESP : public TS_MESSAGE
{
	char successmessage[8];
	uint64_t uk1;
	uint64_t uk2;
	uint32_t exp;
	uint32_t level;
	uint32_t license;
	static const uint16_t packetID = 2097;
};
struct BM_SC_QUEST_DAY_COIN2_RESP : public TS_MESSAGE
{
	char message[17]; //ALREADY_GET_COIN
	static const uint16_t packetID = 2298;
};
struct BM_SC_DEBUG_ACCESS : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2274;
};
struct BM_SC_RUN_CLIENT_SIDE_SCRIPT : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2353;
};
struct BM_SC_QUEST_DAY_COIN_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2296;
};
struct BM_SC_ENTER_INVENTORY_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2079;
};
struct BM_SC_LEAVE_INVENTORY_RESP : public TS_MESSAGE
{
	char successmessage[8];
	static const uint16_t packetID = 2081;
};
struct BM_SC_QUEST_LIST_RESP : public TS_MESSAGE
{
	char successmessage[8];

	static const uint16_t packetID = 2107;
};
struct BM_SC_PLAYER_DISGUISE_RESP : public TS_MESSAGE
{
	char successmessage[8];

	static const uint16_t packetID = 2341;
};

struct BM_SC_MMO_COIN_ENTER_RESP : public TS_MESSAGE
{
	char successmessage[8];
	
	static const uint16_t packetID = 2022;
};

#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
