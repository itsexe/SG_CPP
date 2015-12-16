#include <Packets/Relay/RelayPackets.h>
#include <Networking/General/SG_ClientSession.h>
#include "SG_RelayHandler.h"
#include <Tools/SG_Logger.h>

void SG_RelayHandler::HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const NM_SC_LOGIN* packet)
{
	//SG_Logger::instance().log("Unknown Packet ID[" + std::to_string(packet->id) + "] Size[" + std::to_string(packet->size) + "]", SG_Logger::kLogLevelPacket);

}



