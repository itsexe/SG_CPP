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