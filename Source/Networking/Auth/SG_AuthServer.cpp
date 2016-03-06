#include "SG_AuthServer.h"
#include <string>
#include <random>
#include "Tools/SG_Logger.h"
#include "Handlers/Auth/SG_AuthHandler.h"
#include "Packets/Auth/LoginPackets.h"
#include <Tools/SG_DataConverter.h>

bool SG_AuthServer::OnClientConnected(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log("[" + pSession->m_Player->SessionKey + "] connected from: " + pSession->getSocket().remote_endpoint().address().to_string(), SG_Logger::kLogLevelAuth);
	return true;
}

void SG_AuthServer::OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log("[" + pSession->m_Player->SessionKey + "] disconnected", SG_Logger::kLogLevelAuth);
}

bool SG_AuthServer::OnPacketReceived(const boost::shared_ptr<SG_ClientSession> pSession, const TS_MESSAGE* packet)
{
	switch (packet->id)
	{
	case  XX_SC_KEEP_ALIVE::packetID:
		pSession->m_Player->UpdateLastKeepAlive();
		return true;
	case TS_CA_VERSION::packetID:
		SG_AuthHandler::CheckClientVersion(pSession, static_cast<const TS_CA_VERSION*>(packet));
		break;
	case TS_CA_ACCOUNT_DES::packetID:
		SG_AuthHandler::CheckClientCredentials(pSession, static_cast<const TS_CA_ACCOUNT_DES*>(packet));
		break;
	case TS_CA_SERVER_LIST::packetID:
		SG_AuthHandler::SendServerList(pSession, static_cast<const TS_CA_SERVER_LIST*>(packet));
		break;
	case TS_CA_SELECT_SERVER::packetID:
		SG_AuthHandler::SelectServer(pSession, static_cast<const TS_CA_SELECT_SERVER*>(packet));
		break;
	default:
		std::stringstream ss;
		SG_DataConverter::BytebufferToString(reinterpret_cast<uint8_t*>(&packet), packet->size, ss);
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "] Content[" + ss.str() + "]",SG_Logger::kLogLevelPacket);
	}
	return true;
}

