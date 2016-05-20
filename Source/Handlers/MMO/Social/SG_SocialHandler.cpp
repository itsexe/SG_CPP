#include "SG_SocialHandler.h"
#include "Packets/MMO/Social/SocialPacketsResponse.h"
#include "Networking/General/SG_ServerBase.h"

void SG_SocialHandler::HandleMSN(const boost::shared_ptr<SG_ClientSession> Session)
{
	MM_SC_MSN_RESP response;
	MM_SC_MSN_RESP::initMessage<MM_SC_MSN_RESP>(&response);
	memcpy(response.successmessage, "SUCCESS", 8);
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	response.uk4 = 1;
	Session->SendPacketStruct(&response);
}

void SG_SocialHandler::FindUser(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_MSN_FIND_USER* packet)
{
	MySQLQuery qry(Session->SQLConn, "Select id from Accounts where Name =  ?;");
	qry.setString(1, std::string(packet->username, packet->username + 42));
	qry.ExecuteQuery();
	if (qry.GetResultRowCount()) // Some error occured. The Client will timeout after a few seconds.
	{
		//User found
		MM_SC_MSN_FIND_USER_RESP response;
		MM_SC_MSN_FIND_USER_RESP::initMessage<MM_SC_MSN_FIND_USER_RESP>(&response);
		memcpy(response.successmessage, "SUCCESS", 8);
		response.successmessage[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}
	else
	{
		//User not found (Send packet just to test)
		MM_SC_MSN_FIND_USER_RESP response;
		MM_SC_MSN_FIND_USER_RESP::initMessage<MM_SC_MSN_FIND_USER_RESP>(&response);
		memcpy(response.successmessage, "SUCCESS", 8);
		response.successmessage[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}

}

void SG_SocialHandler::FriendRequest(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_FRIEND_REQUEST* packet)
{
	//TODO: Add request to database
	MM_SC_FRIEND_REQUEST_RESP response;
	MM_SC_FRIEND_REQUEST_RESP::initMessage<MM_SC_FRIEND_REQUEST_RESP>(&response);
	memcpy(response.successmessage, "SUCCESS", 8);
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_SocialHandler::CreateClan(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CLAN_CREATION* packet)
{
	BM_SC_CLAN_CREATION_RESP response;
	BM_SC_CLAN_CREATION_RESP::initMessage<BM_SC_CLAN_CREATION_RESP>(&response);
	memcpy(response.successmessage, "SUCCESS", 8);
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
		memcpy(response.successmessage, "SUCCESS", 8);
		response.successmessage[7] = static_cast<uint8_t>(0);

		// TODO
		// Clean this shit up. I'm currently to tired for this.

		memcpy(response.clanname, "Testclan <3",87);
		memcpy(response.clantag, "TES",4);
		memcpy(response.charname, Session->m_Player->charname.c_str(),43);
		memcpy(response.zoneinfo, Session->m_Player->zoneinfo.c_str(),121);
		memcpy(response.biostr, Session->m_Player->biostr.c_str(),218);
		

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
		response.chartype = static_cast<uint8_t>(Session->m_Player->chartype);
		response.license = Session->m_Player->license;
		response.level = static_cast<uint16_t>(Session->m_Player->charlevel);

		Session->m_Server->SendBroadcast(&response);
	}
}
void SG_SocialHandler::UpdateMateInfo(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_UPDATE_MYMATEINFO* packet)
{
	Session->m_Player->age = packet->age;
	Session->m_Player->zoneid = packet->zoneid;
	Session->m_Player->zoneinfo = std::string(packet->zoneinfo);
	Session->m_Player->biostr = std::string(packet->biostr);
	Session->m_Player->gender = packet->gender;
	Session->m_Player->isprivate = packet->isprivate;
	Session->m_Server->SaveChar(Session);

	//Todo: Maybe send this to mates

	BM_SC_UPDATE_MYMATEINFO_RESP response;
	BM_SC_UPDATE_MYMATEINFO_RESP::initMessage<BM_SC_UPDATE_MYMATEINFO_RESP>(&response);
	memcpy(response.successmessage, "SUCCESS", 8);
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);

}
