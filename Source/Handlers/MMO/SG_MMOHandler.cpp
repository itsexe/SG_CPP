#include "SG_MMOHandler.h"
#include "SG_Config.h"
#include "Tools/SG_Logger.h"
#include "Tools/Encryption/DesPasswordCipher.h"
#include "Tools/SG_DataConverter.h"
#include "Packets/Auth/LoginPackets.h"
#include "Packets/Auth/LoginPacketsResponse.h"
#include <Packets/MMO/MMOPacketsResponse.h>


void SG_MMOHandler::HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet)
{

	std::string skey(packet->sessionKey, packet->sessionKey + 33);
	Session->m_Player->SessionKey = skey;
	Session->m_Player->SessionKey.resize(32);
	SG_Logger::instance().log(Session->getSocket().remote_endpoint().address().to_string() + " has Sessionkey " + Session->m_Player->SessionKey, SG_Logger::kLogLevelMMO);	
	
	//Get playerdata
	MySQLQuery qry(Session->SQLConn, "SELECT username, first_login, char_type, char_level, char_gpotatos, char_rupees, char_coins, char_questpoints FROM sg_account where auth_key = ?;");
	qry.setString(1, Session->m_Player->SessionKey);
	qry.ExecuteQuery();
	if (qry.GetResultRowCount()) // Some error occured. The Client will timeout after a few seconds.
	{
		Session->m_Player->charname = qry.getString(1, "username");
		Session->m_Player->firstlogin = qry.getInt(1, "first_login");
		Session->m_Player->chartype = qry.getInt(1, "char_type");
		Session->m_Player->charlevel = qry.getInt(1, "char_level");
		Session->m_Player->gpotatos = qry.getInt(1, "char_gpotatos");
		Session->m_Player->rupees = qry.getInt(1, "char_rupees");
		Session->m_Player->coins = qry.getInt(1, "char_coins");
		Session->m_Player->questpoints = qry.getInt(1, "char_questpoints");

		//Send login successfull
		BM_SC_LOGIN_RESP response;
		BM_SC_LOGIN_RESP::initMessage<BM_SC_LOGIN_RESP>(&response);
		strcpy_s(response.resonse, static_cast<std::string>("SUCCESS").c_str());
		response.resonse[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}
	else
	{
		//kick client
		BM_SC_LOGIN_RESP_FAILURE response;
		BM_SC_LOGIN_RESP_FAILURE::initMessage<BM_SC_LOGIN_RESP_FAILURE>(&response);
		strcpy_s(response.resonse, static_cast<std::string>("INVALID_REQUEST").c_str());
		response.resonse[15] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}
}

void SG_MMOHandler::HandleCharCreation(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_CHAR* packet)
{
	//std::cout << packet << std::endl;
	//TODO
}

void SG_MMOHandler::SendCharList(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_PLAYER_CHAR_LIST_RESP response;
	BM_SC_PLAYER_CHAR_LIST_RESP::initMessage<BM_SC_PLAYER_CHAR_LIST_RESP>(&response);
	strcpy_s(response.resonse, static_cast<std::string>("SUCCESS").c_str());
	response.resonse[7] = static_cast<uint8_t>(0);
	strcpy_s(response.charname, Session->m_Player->Username.c_str());
	for (auto i = Session->m_Player->Username.length(); i != 43; i++)
	{
		response.charname[i] = static_cast<uint8_t>(0);
	}
	response.firstlogin = Session->m_Player->firstlogin; //0 will push the Player to the Charcreation
	response.chartype = Session->m_Player->chartype;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SelectChar(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_SELECT_CHAR_RESP response;
	BM_SC_SELECT_CHAR_RESP::initMessage<BM_SC_SELECT_CHAR_RESP>(&response);
	strcpy_s(response.resonse, static_cast<std::string>("SUCCESS").c_str());
	response.resonse[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendTrickList(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_TRICK_LIST_RESP response;
	BM_SC_TRICK_LIST_RESP::initMessage<BM_SC_TRICK_LIST_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendPlayerInfo(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_PLAYER_INFO_RESP response;
	BM_SC_PLAYER_INFO_RESP::initMessage<BM_SC_PLAYER_INFO_RESP>(&response);

	//Set string values
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	strcpy_s(response.mapname1, static_cast<std::string>("ID1_Testo_2").c_str());
	strcpy_s(response.mapname2, static_cast<std::string>("ID1_Test").c_str());

	//Fill empty values with nothing
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.mapname1[11] = static_cast<uint8_t>(0);
	response.mapname2[8] = static_cast<uint8_t>(0);

	//Playerstuff
	response.level = Session->m_Player->charlevel;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_BALANCE_INFO_RESP response;
	BM_SC_BALANCE_INFO_RESP::initMessage<BM_SC_BALANCE_INFO_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.rupees = Session->m_Player->rupees;
	response.coin = Session->m_Player->coins;
	response.gpotatos = Session->m_Player->gpotatos;
	response.questpoints = Session->m_Player->questpoints;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendChannellist(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_CHANNEL_LIST_RESP response;
	BM_SC_CHANNEL_LIST_RESP::initMessage<BM_SC_CHANNEL_LIST_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	strcpy_s(response.channelname, static_cast<std::string>("CHANNEL 1").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	for (auto i = static_cast<std::string>("CHANNEL 1").length(); i != 12; i++)
	{
		response.channelname[i] = static_cast<uint8_t>(0);
	}
	response.channelcount = 1;
	response.channelid = 1;
	response.currentplayers = 1;
	response.maximumplayers = 1234;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::EnterChannel(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_CHANNEL* packet)
{
	SG_Logger::instance().log(Session->m_Player->Username + " is joining Channel " + std::to_string(packet->channelid),SG_Logger::kLogLevelMMO);
	BM_SC_ENTER_CHANNEL_RESP response;
	BM_SC_ENTER_CHANNEL_RESP::initMessage<BM_SC_ENTER_CHANNEL_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	response.uk4 = 1;
	Session->SendPacketStruct(&response);
}