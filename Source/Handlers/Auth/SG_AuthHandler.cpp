#include "SG_AuthHandler.h"
#include "SG_Config.h"
#include "Tools/SG_Logger.h"
#include "Packets/Auth/LoginPackets.h"
#include "Packets/Auth/LoginPacketsResponse.h"
#include "Tools/Database/Database.h"
#include "Networking/General/SG_ClientSession.h"
#include "Tools/Encryption/DesPasswordCipher.h"

// EXT_IP
#define EXT_IP "31.38.215.40"

SG_AuthHandler::SG_AuthHandler()
{
}

void SG_AuthHandler::CheckClientVersion(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_VERSION* packet)
{
	Session->m_Player->ClientVersion = packet->szVersion;
	Session->m_Player->ClientLang = packet->szLang;
	if (SG_ClientSession::conf->CheckClientVersion == true)
	{
		if (Session->m_Player->ClientVersion != SG_ClientSession::conf->ClientVersion || Session->m_Player->ClientLang != SG_ClientSession::conf->ClientLanguage)
		{
			SG_Logger::instance().log("[" + Session->m_Player->SessionKey + "]" + " Invalid Clientversion. [" + SG_ClientSession::conf->ClientLanguage + "] <--> [" + Session->m_Player->ClientLang + "] [" + SG_ClientSession::conf->ClientVersion + "] <--> [" + Session->m_Player->ClientVersion + "]", SG_Logger::kLogLevelPlayer);
			return;
		}
	}
	SG_Logger::instance().log("[" + Session->m_Player->SessionKey + "]" + " Client Version okay! [" + Session->m_Player->ClientLang + "] ["+ Session->m_Player->ClientVersion + "]", SG_Logger::kLogLevelPlayer);
}
void SG_AuthHandler::CheckClientCredentials(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet)
{
	Session->m_Player->Username = packet->account;
	std::vector<unsigned char> cryptedPassword (std::begin(packet->password), std::end(packet->password));

	//Decrypt DES Password
	DesPasswordCipher("MERONG").decrypt(&cryptedPassword[0], (int)cryptedPassword.size());
	std::stringstream ss;
	for (size_t i = 0; i < cryptedPassword.size(); ++i)
	{
		if(cryptedPassword[i] != 0)
		ss << cryptedPassword[i];
	}	
	Session->m_Player->Password = ss.str();
	
	SG_Logger::instance().log("[" + Session->m_Player->SessionKey + "] tried to login with Username: " + Session->m_Player->Username + " Password: "+ Session->m_Player->Password, SG_Logger::kLogLevelDebug);
	
	//Check Login using MySQL
	MySQLQuery qry(Session->SQLConn, "SELECT id, verified, banned FROM Accounts where username = ? and password = md5(?);");
	qry.setString(1, Session->m_Player->Username);
	//qry.setString(2, SG_ClientSession::conf->MD5Salt + Session->m_Player->Password);
	qry.setString(2, Session->m_Player->Password);
	std::cout << qry.BuildQueryString() << std::endl;
	qry.ExecuteQuery();
	if (!qry.GetResultRowCount()) // User or password wrong
	{
		LoginDenied(Session, static_cast<const TS_CA_ACCOUNT_DES*>(packet), MSG_SERVER_NOT_EXIST);
	}else
	{
		if (qry.getInt(1, "verified") == 1) // user exist
		{
			if (!qry.getInt(1, "banned")) // everything is fine -> login
			{
				MySQLQuery updatesessionkey(Session->SQLConn, "UPDATE Accounts set Sessionkey = ? where id = ?");
				updatesessionkey.setString(1, Session->m_Player->SessionKey);
				updatesessionkey.setInt(2, qry.getInt(1, "id"));
				updatesessionkey.ExecuteUpdate();
				SG_AuthHandler::AcceptLogin(Session, static_cast<const TS_CA_ACCOUNT_DES*>(packet));
			}
			else //User is banned!
			{
				LoginDenied(Session, static_cast<const TS_CA_ACCOUNT_DES*>(packet), MSG_FAIL_WEB_ID);
			}
		}
		else //User is not verified!
		{
			LoginDenied(Session, static_cast<const TS_CA_ACCOUNT_DES*>(packet), MSG_SERVER_DENIED);
		}
	}
}
void SG_AuthHandler::AcceptLogin(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet)
{
	TS_SC_WE_LOGIN response;
	TS_MESSAGE::initMessage<TS_SC_WE_LOGIN>(&response);
	response.uk1 = 1;
	strcpy_s(response.sessionKey, Session->m_Player->SessionKey.c_str());
	response.uk2 = 700;
	response.uk3 = 1;
	Session->SendPacketStruct(&response);
}

void SG_AuthHandler::LoginDenied(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet, TM_SC_RESULT_error reason)
{
	TM_SC_RESULT response;
	TS_MESSAGE::initMessage<TM_SC_RESULT>(&response);
	response.uk1 = 0;
	response.reason = reason;
	Session->SendPacketStruct(&response);
}

void SG_AuthHandler::SendServerList(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_SERVER_LIST * packet)
{
	TS_CA_SERVER_LIST_RESP response;
	TS_CA_SERVER_LIST_RESP::initMessage<TS_CA_SERVER_LIST_RESP>(&response);

	//TODO: Make this crap dynamic
	response.uk1 = 1;
	response.xID = 100;
	response.Msg_ID = 2;
	response.Lobby_ID = 3;
	response.MMO_ID = 4;
	std::string external_ip = EXT_IP;
	strcpy_s(response.msg_IP, external_ip.c_str()/*SG_ClientSession::conf->msgIP.c_str()*/);
	strcpy_s(response.mmo_IP, external_ip.c_str()/*SG_ClientSession::conf->MMOIP.c_str()*/);
	strcpy_s(response.lobby_IP, external_ip.c_str()/*SG_ClientSession::conf->LobbyIP.c_str()*/);
	for (auto i = external_ip.length(); i != 16; i++)
	{
		response.msg_IP[i] = static_cast<uint8_t>(0);
	}
	for (auto i = external_ip.length(); i != 16; i++)
	{
		response.mmo_IP[i] = static_cast<uint8_t>(0);
	}
	for (auto i = external_ip.length(); i != 16; i++)
	{
		response.lobby_IP[i] = static_cast<uint8_t>(0);
	}
	response.Msg_Port = SG_ClientSession::conf->MsgPort;
	response.Lobby_Port = SG_ClientSession::conf->LobbyPort;
	response.MMO_Port = SG_ClientSession::conf->MMOPort;
	response.CurrentUsers = 0;
	response.MaximumUsers = SG_ClientSession::conf->MaximumUsersPerServer;
	Session->SendPacketStruct(&response);
	std::cout << "server list sent" << std::endl;
}

void SG_AuthHandler::SelectServer(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_SELECT_SERVER * packet)
{
	std::cout << "select server" << std::endl;
	TS_CA_SELECT_SERVER_RESP response;
	TS_CA_SELECT_SERVER_RESP::initMessage<TS_CA_SELECT_SERVER_RESP>(&response);
	response.state = TM_SC_SELECT_SERVER_state::CONNECTION_SUCCES;
	response.uk1 = 1;
	response.uk2 = 2;
	response.serverId = 3;
	Session->SendPacketStruct(&response);
}
