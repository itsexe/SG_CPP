#ifndef PACKETS_LOGIN_RESPONSE
#define PACKETS_LOGIN_RESPONSE

#include "Packets/PacketBaseMessage.h"

#pragma pack(push, 1)
const enum TM_SC_RESULT_error : uint16_t
{
	SUCCESS_INTERNAL = 0, //THIS WILL BE USED FOR INTERNAL COMMUNICATION!
	MSG_SERVER_NOT_EXIST = 1,// wrong login information passed
	MSG_SERVER_DENIED = 6, // connection denied
	MSG_SERVER_ALREADY_EXIST = 9, // alrdy connected. terminate actual connect, try again
	MSG_SERVER_RETRY = 50, // couldnt connect to server, try later
	MSG_FAIL_WEB_ID = 60, // go to www.gpotato.eu and login
	AURORA_RESULT_REPETITION = 70, // to many login try's, temporarly banned
};
const enum TM_SC_SELECT_SERVER_state : uint16_t
{
	CONNECTION_SUCCES = 0, // continue to login screen
	CONNECTION_BROKEN = 1, // connection to server broken/lost. please login again
};
struct TM_SC_RESULT : public TS_MESSAGE
{
	uint16_t uk1;
	TM_SC_RESULT_error reason;
	static const uint16_t packetID = 1001;
};
struct TS_SC_WE_LOGIN : public TS_MESSAGE
{
	uint32_t uk1;
	char sessionKey[33];
	uint32_t uk2;
	uint8_t uk3;
	static const uint16_t packetID = 1009;
};
struct TS_CA_SERVER_LIST_RESP : public TS_MESSAGE
{
	uint16_t uk1;
	uint16_t xID;
	uint16_t Msg_ID;
	uint16_t Lobby_ID;
	uint16_t MMO_ID;
	char msg_IP[16];
	char lobby_IP[16];
	char mmo_IP[16];
	uint32_t Msg_Port;
	uint32_t Lobby_Port;
	uint32_t MMO_Port;
	uint16_t CurrentUsers;
	uint16_t MaximumUsers;
	static const uint16_t packetID = 1012;
};
struct TS_CA_SELECT_SERVER_RESP : public TS_MESSAGE
{
	TM_SC_SELECT_SERVER_state state;
	uint32_t uk1;
	uint32_t uk2;
	uint32_t uk3;
	static const uint16_t packetID = 1007;
};
#pragma pack(pop)

#endif // PACKETS_TS_CA_ACCOUNT_H
