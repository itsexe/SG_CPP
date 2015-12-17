#ifndef HANDLEAUTH
#define HANDLEAUTH
#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "../../Networking/General/SG_ClientSession.h"
#include "../../Packets/Auth/LoginPackets.h"
#include "../../Packets/Auth/LoginPacketsResponse.h"
#include "../../Tools/Database/Database.h"

class SG_AuthHandler
{
public:
	SG_AuthHandler();
	static void CheckClientVersion(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_VERSION* packet);
	static void CheckClientCredentials(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet);
	static void AcceptLogin(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet);
	static void LoginDenied(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet, TM_SC_RESULT_error reason);
	static void SendServerList(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_SERVER_LIST* packet);
	static void SelectServer(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_SELECT_SERVER* packet);

};

#endif