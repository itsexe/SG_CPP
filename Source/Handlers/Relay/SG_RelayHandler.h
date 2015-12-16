#ifndef SG_RelayHandler_H
#define SG_RelayHandler_H
#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include "Packets/Relay/RelayPackets.h"

class SG_RelayHandler
{
public:
	static void HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const NM_SC_LOGIN* packet);

};
 
#endif