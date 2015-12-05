#include "SG_AuthHandler.h"
#include "SG_Config.h"
#include "Tools/SG_Logger.h"
#include "Tools/Encryption/DesPasswordCipher.h"
#include "Tools/SG_DataConverter.h"
#include "Packets/Auth/LoginPackets.h"
#include "Packets/Auth/LoginPacketsResponse.h"
#include "Tools/Database/Database.h"
#include <mysql.h>

SG_AuthHandler::SG_AuthHandler()
{
}

void SG_AuthHandler::CheckClientVersion(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_VERSION* packet)
{
	Session->m_Player->ClientVersion = packet->szVersion;
	Session->m_Player->ClientLang = packet->szLang;
	if (SG_Config::CheckClientVersion == true)
	{
		if (Session->m_Player->ClientVersion != SG_Config::ClientVersion || Session->m_Player->ClientLang != SG_Config::ClientLanguage)
		{
			SG_Logger::instance().log("[" + Session->m_Player->SessionKey + "]" + " Invalid Clientversion. [" + SG_Config::ClientLanguage + "] <--> [" + Session->m_Player->ClientLang + "] [" + SG_Config::ClientVersion + "] <--> [" + Session->m_Player->ClientVersion + "]", SG_Logger::kLogLevelPlayer);
			return;
		}
	}
	SG_Logger::instance().log("[" + Session->m_Player->SessionKey + "]" + " Client Version okay! [" + Session->m_Player->ClientLang + "] ["+ Session->m_Player->ClientVersion + "]", SG_Logger::kLogLevelPlayer);
}
void SG_AuthHandler::CheckClientCredentials(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_ACCOUNT_DES* packet)
{
	Session->m_Player->Username = packet->account;
	std::vector<unsigned char> cryptedPassword (std::begin(packet->password), std::end(packet->password));

	//Session->m_Player->Password = packet->password;

	//Decrypt DES Password (currently not working)
	//DesPasswordCipher("!_a^Rc*|#][Ych$~'(M _!d4aUo^%${T!~}h*&X%").decrypt(&cryptedPassword[0], (int)cryptedPassword.size());
	Session->m_Player->Password = packet->password;
	
	SG_Logger::instance().log("[" + Session->m_Player->SessionKey + "] tried to login with Username: " + Session->m_Player->Username + " Password: "+ Session->m_Player->Password, SG_Logger::kLogLevelDebug);
	
	//Check Login using MySQL
	MySQLQuery qry(Session->SQLConn, "SELECT id, verified, banned FROM sg_account where user = ? and password = md5(?);");
	qry.setString(1, Session->m_Player->Username);
	qry.setString(2, SG_Config::MD5Salt + Session->m_Player->Password);
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
				MySQLQuery updatesessionkey(Session->SQLConn, "UPDATE sg_account set auth_key = ? where id = ?");
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
	SG_Config::init();
	//TODO: Make this crap dynamic
	response.uk1 = 1;
	response.xID = 100;
	response.Msg_ID = 2;
	response.Lobby_ID = 3;
	response.MMO_ID = 4;
	strcpy_s(response.msg_IP, SG_Config::msgIP.c_str());
	strcpy_s(response.mmo_IP, SG_Config::MMOIP.c_str());
	strcpy_s(response.lobby_IP, SG_Config::LobbyIP.c_str());
	for (auto i = SG_Config::msgIP.length(); i != 16; i++)
	{
		response.msg_IP[i] = static_cast<uint8_t>(0);
	}
	for (auto i = SG_Config::MMOIP.length(); i != 16; i++)
	{
		response.mmo_IP[i] = static_cast<uint8_t>(0);
	}
	for (auto i = SG_Config::LobbyIP.length(); i != 16; i++)
	{
		response.lobby_IP[i] = static_cast<uint8_t>(0);
	}
	response.Msg_Port = SG_Config::MsgPort;
	response.Lobby_Port = SG_Config::LobbyPort;
	response.MMO_Port = SG_Config::MMOPort;
	response.CurrentUsers = 0;
	response.MaximumUsers = SG_Config::MaximumUsersPerServer;
	Session->SendPacketStruct(&response);
}

void SG_AuthHandler::SelectServer(const boost::shared_ptr<SG_ClientSession> Session, const TS_CA_SELECT_SERVER * packet)
{
	TS_CA_SELECT_SERVER_RESP response;
	TS_CA_SELECT_SERVER_RESP::initMessage<TS_CA_SELECT_SERVER_RESP>(&response);
	response.state = TM_SC_SELECT_SERVER_state::CONNECTION_SUCCES;
	response.uk1 = 0;
	response.uk2 = 0;
	response.uk3 = 0;
	Session->SendPacketStruct(&response);
}
