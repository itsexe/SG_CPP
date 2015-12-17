#include "SG_RelayServer.h"
#include <string>
#include "Tools/SG_Logger.h"
#include <Packets/Relay/RelayPackets.h>
#include <Handlers/Relay/SG_RelayHandler.h>

bool SG_RelayServer::OnClientConnected(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log("[" + pSession->m_Player->SessionKey + "] connected from: " + pSession->getSocket().remote_endpoint().address().to_string(), SG_Logger::kLogLevelRelay);
	return true;
}

void SG_RelayServer::OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log("[" + pSession->m_Player->SessionKey + "] disconnected!", SG_Logger::kLogLevelRelay);
}

bool SG_RelayServer::OnPacketReceived(const boost::shared_ptr<SG_ClientSession> pSession, const TS_MESSAGE* packet)
{
	switch (packet->id)
	{
	case NM_SC_KEEP_ALIVE::packetID:
		//do nothing
		break;
	case NM_SC_KEEP_ALIVE_INGAME::packetID:
		//do nothing
		break;
	case NM_SC_LOGIN::packetID:
		SG_RelayHandler::HandleLogin(pSession, static_cast<const NM_SC_LOGIN*>(packet));
		break;
	case NM_SC_EXPIRE::packetID: //Client finished loading
		SG_RelayHandler::SendServerTick(pSession);
		SG_RelayHandler::ReadyGame(pSession);

		SG_RelayHandler::StartGame(pSession);
		break;
	case Playerinfo::packetID:
		SG_RelayHandler::handleplayerinfo(pSession, static_cast<const Playerinfo*>(packet));
		break;
	default:
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]",SG_Logger::kLogLevelPacket);
	}

	return true;
}

