#include "SG_LobbyServer.h"
#include <string>
#include "Tools/SG_Logger.h"
#include <Tools/SG_DataConverter.h>

bool SG_LobbyServer::OnClientConnected(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log("[" + pSession->m_Player->SessionKey + "] connected from: " + pSession->getSocket().remote_endpoint().address().to_string(), SG_Logger::kLogLevelLobby);
	return true;
}

void SG_LobbyServer::OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log("[" + pSession->m_Player->SessionKey + "] disconnected!", SG_Logger::kLogLevelLobby);
}

bool SG_LobbyServer::OnPacketReceived(const boost::shared_ptr<SG_ClientSession> pSession, const TS_MESSAGE* packet)
{
	switch (packet->id)
	{
	case 1:
		break;
	default:
		std::stringstream ss;
		SG_DataConverter::BytebufferToString(reinterpret_cast<uint8_t*>(&packet), packet->size, ss);
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "] Content[" + ss.str() + "]", SG_Logger::kLogLevelPacket);
	}

	return true;
}

