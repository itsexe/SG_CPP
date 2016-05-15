#include "Packets/Relay/RelayPackets.h"
#include "Networking/General/SG_ClientSession.h"
#include "SG_RelayHandler.h"
#include "Tools/SG_Logger.h"
#include "Packets/Relay/RelayPacketsResponse.h"
#include "Packets/MMO/MMOPacketsResponse.h"
#include <Tools/SG_DataConverter.h>

void SG_RelayHandler::HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const NM_SC_LOGIN* packet)
{
	//SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]", SG_Logger::kLogLevelPacket);

}

void SG_RelayHandler::ReadyGame(const boost::shared_ptr<SG_ClientSession> Session)
{
	NM_SC_READY_GAME_RESP response;
	NM_SC_READY_GAME_RESP::initMessage<NM_SC_READY_GAME_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_RelayHandler::StartGame(const boost::shared_ptr<SG_ClientSession> Session)
{
	NM_SC_START_GAME_RESP response;
	NM_SC_START_GAME_RESP::initMessage<NM_SC_START_GAME_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

//? ========================================================================
void SG_RelayHandler::StartGame2(const boost::shared_ptr<SG_ClientSession> Session)
{
	NM_SC_START_GAME2_RESP response;
	NM_SC_START_GAME2_RESP::initMessage<NM_SC_START_GAME2_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_RelayHandler::SendServerTick(const boost::shared_ptr<SG_ClientSession> Session)
{
	NM_SC_GET_SERVER_TICK_RESP response;
	NM_SC_GET_SERVER_TICK_RESP::initMessage<NM_SC_GET_SERVER_TICK_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_RelayHandler::handleplayerinfo(const boost::shared_ptr<SG_ClientSession> Session, const Playerinfo* packet)
{
	Playerinfo_RESP response;
	Playerinfo_RESP::initMessage<Playerinfo_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_RelayHandler::KickClient(const boost::shared_ptr<SG_ClientSession> Session)
{

	NM_SC_EXPIRE_RESP response;
	NM_SC_EXPIRE_RESP::initMessage<NM_SC_EXPIRE_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}


