#include "SG_LobbyServer.h"
#include <string>
#include "Constructors/SG_Packets.h"
#include "Tools/SG_Logger.h"

bool SG_LobbyServer::OnClientConnected(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log(pSession->getSocket().remote_endpoint().address().to_string() + " connected!", SG_Logger::kLogLevelLobby);
	return true;
}

void SG_LobbyServer::OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log(pSession->m_Player->SessionKey + " disconnected!", SG_Logger::kLogLevelLobby);
}

bool SG_LobbyServer::OnPacketReceived(const boost::shared_ptr<SG_ClientSession> pSession, const TS_MESSAGE* packet)
{
	switch (packet->id)
	{
	case SG_Packets::Recv::XX_SC_KEEP_ALIVE_recv:
		pSession->m_Player->UpdateLastKeepAlive();
		return true;
	default:
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]",SG_Logger::kLogLevelPacket);
	}

	return true;
}

