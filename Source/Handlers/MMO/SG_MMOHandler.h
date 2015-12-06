#ifndef SG_MMOHandler_H
#define SG_MMOHandler_H
#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/General/SG_ClientSession.h"
#include "Packets/MMO/MMOPackets.h"

class SG_MMOHandler
{
public:
	static void HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet);
	static void HandleCharCreation(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_CHAR* packet);
	static void SendCharList(const boost::shared_ptr<SG_ClientSession> Session);
	static void SelectChar(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendTrickList(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendPlayerInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session);
	static void SendChannellist(const boost::shared_ptr<SG_ClientSession> Session);
	static void EnterChannel(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_CHANNEL* packet);

};

#endif