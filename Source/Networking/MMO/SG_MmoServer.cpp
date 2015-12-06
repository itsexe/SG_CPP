#include "SG_MmoServer.h"
#include <string>
#include <random>
#include "Constructors/SG_Packets.h"
#include "Tools/SG_Logger.h"
#include "Handlers/MMO/SG_MMOHandler.h"
#include "Packets/Auth/LoginPackets.h"
#include <Packets/MMO/MMOPackets.h>


bool SG_MmoServer::OnClientConnected(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log(pSession->getSocket().remote_endpoint().address().to_string() + " connected!", SG_Logger::kLogLevelMMO);
	return true;
}

void SG_MmoServer::OnClientDisconnect(const boost::shared_ptr<SG_ClientSession> pSession)
{
	SG_Logger::instance().log(pSession->getSocket().remote_endpoint().address().to_string() + " disconnected!", SG_Logger::kLogLevelMMO);
}

bool SG_MmoServer::OnPacketReceived(const boost::shared_ptr<SG_ClientSession> pSession, const TS_MESSAGE* packet)
{
	switch (packet->id)
	{
	case SG_Packets::Recv::XX_SC_KEEP_ALIVE_recv:
		pSession->m_Player->UpdateLastKeepAlive();
		return true;
	case BM_SC_LOGIN::packetID:
		SG_MMOHandler::HandleLogin(pSession, static_cast<const BM_SC_LOGIN*>(packet));
		SG_MMOHandler::SendCharList(pSession);
		break;
	case BM_SC_SELECT_CHAR::packetID:
		SG_MMOHandler::SelectChar(pSession);
		//Sometimes the client wont request this data, so we send it after the char selection without a request.
		SG_MMOHandler::SendPlayerInfo(pSession);
		SG_MMOHandler::SendTrickList(pSession);
		break;
	case BM_SC_PLAYER_INFO::packetID:
		SG_MMOHandler::SendPlayerInfo(pSession);
		break;
	case BM_SC_TRICK_LIST::packetID:
		SG_MMOHandler::SendTrickList(pSession);
		break;
	case BM_SC_CHANNEL_LIST::packetID:
		SG_MMOHandler::SendChannellist(pSession);
		break;
	case BM_SC_BALANCE_INFO::packetID:
		SG_MMOHandler::SendBalanceInfo(pSession);
		break;
	case BM_SC_ENTER_CHANNEL::packetID:
		SG_MMOHandler::EnterChannel(pSession, static_cast<const BM_SC_ENTER_CHANNEL*>(packet));
		break;
	case BM_SC_CREATE_CHAR::packetID:
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]", SG_Logger::kLogLevelPacket);
		SG_MMOHandler::HandleCharCreation(pSession, static_cast<const BM_SC_CREATE_CHAR*>(packet));
		break;
	default:
		SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]",SG_Logger::kLogLevelPacket);
	}

	return true;
}
