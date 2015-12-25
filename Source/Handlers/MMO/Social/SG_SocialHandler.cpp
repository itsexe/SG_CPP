#include "SG_SocialHandler.h"
#include <Packets/MMO/Social/SocialPacketsResponse.h>

void SG_SocialHandler::HandleMSN(const boost::shared_ptr<SG_ClientSession> Session)
{
	MM_SC_MSN_RESP response;
	MM_SC_MSN_RESP::initMessage<MM_SC_MSN_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	response.uk4 = 1;
	Session->SendPacketStruct(&response);
}

void SG_SocialHandler::FindUser(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_MSN_FIND_USER* packet)
{
	MySQLQuery qry(Session->SQLConn, "Select id from Chars where Name =  ?;");
	qry.setString(1, std::string(packet->username, packet->username + 42));
	qry.ExecuteQuery();
	if (qry.GetResultRowCount()) // Some error occured. The Client will timeout after a few seconds.
	{
		//User found
		MM_SC_MSN_FIND_USER_RESP response;
		MM_SC_MSN_FIND_USER_RESP::initMessage<MM_SC_MSN_FIND_USER_RESP>(&response);
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
		response.successmessage[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}
	else
	{
		//User not found (Send packet just to test)
		MM_SC_MSN_FIND_USER_RESP response;
		MM_SC_MSN_FIND_USER_RESP::initMessage<MM_SC_MSN_FIND_USER_RESP>(&response);
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
		response.successmessage[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}

}

void SG_SocialHandler::FriendRequest(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_FRIEND_REQUEST* packet)
{
	//TODO: Add request to database
	MM_SC_FRIEND_REQUEST_RESP response;
	MM_SC_FRIEND_REQUEST_RESP::initMessage<MM_SC_FRIEND_REQUEST_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_SocialHandler::CreateClan(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CLAN_CREATION* packet)
{
	BM_SC_CLAN_CREATION_RESP response;
	BM_SC_CLAN_CREATION_RESP::initMessage<BM_SC_CLAN_CREATION_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_SocialHandler::HandleMateInfo(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MATE_INFO* packet)
{
	std::string charname(packet->charname);
	if (charname == Session->m_Player->charname)
	{
		BM_SC_MATE_INFO_RESP response;
		BM_SC_MATE_INFO_RESP::initMessage<BM_SC_MATE_INFO_RESP>(&response);
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
		response.successmessage[7] = static_cast<uint8_t>(0);

		// TODO
		// Clean this shit up. I'm currently to tired for this.

		strcpy_s(response.clanname, static_cast<std::string>("Testclan <3").c_str());
		strcpy_s(response.clantag, static_cast<std::string>("TES").c_str());
		strcpy_s(response.charname, Session->m_Player->charname.c_str());
		strcpy_s(response.zoneinfo, Session->m_Player->zoneinfo.c_str());
		strcpy_s(response.biostr, Session->m_Player->biostr.c_str());




		for (auto i = static_cast<std::string>("Testclan <3").length(); i != 87; ++i)
		{
			response.clanname[i] = static_cast<uint8_t>(0);
		}
		for (auto i = Session->m_Player->charname.length(); i != 43; ++i)
		{
			response.charname[i] = static_cast<uint8_t>(0);
		}
		for (auto i = Session->m_Player->zoneinfo.length(); i != 121; ++i)
		{
			response.zoneinfo[i] = static_cast<uint8_t>(0);
		}
		for (auto i = Session->m_Player->biostr.length(); i != 218; ++i)
		{
			response.biostr[i] = static_cast<uint8_t>(0);
		}

		response.age = Session->m_Player->age;
		response.zoneid = Session->m_Player->zoneid;
		response.chartype = Session->m_Player->chartype;
		response.license = Session->m_Player->license;
		response.level = Session->m_Player->charlevel;

		Session->SendPacketStruct(&response);
	}
}