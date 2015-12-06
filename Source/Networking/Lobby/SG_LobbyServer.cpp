#include "SG_LobbyServer.h"
#include <string>
#include <random>
#include "Constructors/SG_Packets.h"
#include "Tools/SG_Logger.h"
#include "Handlers/MMO/SG_MMOHandler.h"
#include "Packets/Auth/LoginPackets.h"
#include <Packets/MMO/MMOPackets.h>


bool SG_LobbyServer::OnClientConnected(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log(pSession->getSocket().remote_endpoint().address().to_string() + " connected!", SG_Logger::kLogLevelLobby);
	return true;
}

void SG_LobbyServer::OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log(pSession->getSocket().remote_endpoint().address().to_string() + " disconnected!", SG_Logger::kLogLevelLobby);
}

bool SG_LobbyServer::OnPacketReceived(const boost::shared_ptr<SG_ClientSession> pSession, const TS_MESSAGE* packet)
{
	switch (packet->id)
	{
	case SG_Packets::Recv::XX_SC_KEEP_ALIVE_recv:
		pSession->m_Player->UpdateLastKeepAlive();
		return true;
	case BM_SC_LOGIN::packetID:
		SG_MMOHandler::HandleLogin(pSession, static_cast<const BM_SC_LOGIN*>(packet));
		break;
	default:
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]",SG_Logger::kLogLevelPacket);
	}

	return true;
}

