#include "SG_MMOHandler.h"
#include "Tools/SG_Logger.h"
#include "Packets/MMO/MMOPacketsResponse.h"
#include <boost/make_shared.hpp>
#include <Networking/General/SG_ServerBase.h>

void SG_MMOHandler::HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet)
{

	std::string skey(packet->sessionKey, packet->sessionKey + 33);
	Session->m_Player->SessionKey = skey;
	Session->m_Player->SessionKey.resize(32);
	
	//Get Accountsettings
	MySQLQuery accqry(Session->SQLConn, "Select id, ingamecash from Accounts where Sessionkey = ?;");
	accqry.setString(1, Session->m_Player->SessionKey);
	accqry.ExecuteQuery();
	if (accqry.GetResultRowCount()) // Some error occured. The Client will timeout after a few seconds.
	{
		Session->m_Player->playerid = accqry.getInt(1, "id");
		//Get Chars
		MySQLQuery qry(Session->SQLConn, "Select id, Name, Rank, CharType, Level, XP, License, Rupees, Coins, Questpoints from Chars where AccountID =  ?;");
		qry.setInt(1, Session->m_Player->playerid);
		qry.ExecuteQuery();
		if (qry.GetResultRowCount()) // Some error occured. The Client will timeout after a few seconds.
		{
			Session->m_Player->charname = qry.getString(1, "Name");
			Session->m_Player->chartype = qry.getInt(1, "CharType");
			Session->m_Player->charlevel = qry.getInt(1, "Level");
			Session->m_Player->gpotatos = qry.getInt(1, "Rupees");
			Session->m_Player->rupees = qry.getInt(1, "Rupees");
			Session->m_Player->coins = qry.getInt(1, "Coins");
			Session->m_Player->exp = qry.getInt(1, "XP");
			Session->m_Player->rank = qry.getInt(1, "Rank");
			Session->m_Player->license = qry.getInt(1, "License");
			Session->m_Player->questpoints = qry.getInt(1, "Questpoints");
			Session->m_Player->charcreated = 1;
		}
		else
		{
			Session->m_Player->charcreated = 0;
		}
		//Send login successfull
		BM_SC_LOGIN_RESP response;
		BM_SC_LOGIN_RESP::initMessage<BM_SC_LOGIN_RESP>(&response);
		strcpy_s(response.resonse, static_cast<std::string>("SUCCESS").c_str());
		response.resonse[7] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}else
	{
		//kick client
		BM_SC_LOGIN_RESP_FAILURE response;
		BM_SC_LOGIN_RESP_FAILURE::initMessage<BM_SC_LOGIN_RESP_FAILURE>(&response);
		strcpy_s(response.resonse, static_cast<std::string>("INVALID_REQUEST").c_str());
		response.resonse[15] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}
}

void SG_MMOHandler::CreateChar(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_CHAR* packet)
{
	BM_SC_CREATE_CHAR_RESP response;
	BM_SC_CREATE_CHAR_RESP::initMessage<BM_SC_CREATE_CHAR_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);

	//Insert everything in Database
	MySQLQuery qry(Session->SQLConn, "INSERT INTO Chars (Name, Rank, CharType, Level, XP, License, Rupees, Coins, Questpoints, AccountID) VALUES (?,0,1,0,0,0,10,10,0,?);");
	qry.setString(1, packet->charname);
	qry.setInt(2, Session->m_Player->playerid);
	qry.ExecuteInsert();
	SG_Logger::instance().log(Session->m_Player->SessionKey + " has charname " + Session->m_Player->charname, SG_Logger::kLogLevelMMO);

	//std::cout << packet << std::endl;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendCharList(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAR_LIST* packet)
{
	BM_SC_PLAYER_CHAR_LIST_RESP response;
	BM_SC_PLAYER_CHAR_LIST_RESP::initMessage<BM_SC_PLAYER_CHAR_LIST_RESP>(&response);
	strcpy_s(response.resonse, static_cast<std::string>("SUCCESS").c_str());
	response.resonse[7] = static_cast<uint8_t>(0);
	strcpy_s(response.charname, Session->m_Player->charname.c_str());
	for (auto i = Session->m_Player->charname.length(); i != 43; i++)
	{
		response.charname[i] = static_cast<uint8_t>(0);
	}
	response.firstlogin = Session->m_Player->charcreated; //0 will push the Player to the Charcreation
	response.chartype = Session->m_Player->chartype;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SelectChar(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_SELECT_CHAR_RESP response;
	BM_SC_SELECT_CHAR_RESP::initMessage<BM_SC_SELECT_CHAR_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendTrickList(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_TRICK_LIST_RESP response;
	BM_SC_TRICK_LIST_RESP::initMessage<BM_SC_TRICK_LIST_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);

	response.trickcount = 13;
	std::copy(std::begin(Session->m_Player->tricks), std::end(Session->m_Player->tricks), std::begin(response.tricklist));

	BM_SC_TRICK_LIST_RESP::recalcheader<BM_SC_TRICK_LIST_RESP>(&response);
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
	
	response.uk8 = 5;
	response.sp2id = 2;
	response.sp2size = 12;
	response.uk17 = 5;
	response.uk18 = 5;

	response.sp4id = 4;
	response.sp4size = 12;
	response.uk19 = 5;
	response.uk20 = 6;
	response.uk31 = 7;

	response.sp64id = 64;
	response.sp64size = 16;
	response.uk32 = 7;
	response.uk33 = 8;
	response.uk34 = 9;
	response.uk35 = 10;

	response.sp512id = 512;
	response.sp512size = 44;

	response.sp1024id = 511;
	response.sp1024size = 12;
	response.count1 = 2;
	response.count2 = 1;
	response.count3 = 2;



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

void SG_MMOHandler::SendCashBalanceInfo(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_CASH_BALANCE_INFO_RESP response;
	BM_SC_CASH_BALANCE_INFO_RESP::initMessage<BM_SC_CASH_BALANCE_INFO_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.coin = Session->m_Player->coins;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendLevelInfo(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_LEVEL_INFO_RESP response;
	BM_SC_LEVEL_INFO_RESP::initMessage<BM_SC_LEVEL_INFO_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.exp = Session->m_Player->exp;
	response.level = static_cast<uint32_t>(Session->m_Player->charlevel);
	response.license = Session->m_Player->license;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendInventory(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_INVENTORY_RESP response;
	BM_SC_INVENTORY_RESP::initMessage<BM_SC_INVENTORY_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	
	response.count = static_cast<uint16_t>(Session->m_Player->items.size());
	/*for (const auto &iter : Session->m_Player->items)
	{
		response.items.push_back(iter);
	}*/
	BM_SC_INVENTORY_RESP::recalcheader<BM_SC_INVENTORY_RESP>(&response);
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
	SG_Logger::instance().log(Session->m_Player->charname + " is joining Channel " + std::to_string(packet->channelid),SG_Logger::kLogLevelMMO);
	BM_SC_ENTER_CHANNEL_RESP response;
	BM_SC_ENTER_CHANNEL_RESP::initMessage<BM_SC_ENTER_CHANNEL_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	response.uk4 = 1;
	Session->SendPacketStruct(&response);
	if(Session->m_Player->rank == 3)
	{
		UnlockDebugAccess(Session);
	}
}

void SG_MMOHandler::LeaveChannel(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_LEAVE_CHANNEL_RESP response;
	BM_SC_LEAVE_CHANNEL_RESP::initMessage<BM_SC_LEAVE_CHANNEL_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::HandlePositionUpdate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MMO_GAME_MESSAGE* packet)
{
	//TODO: send this to other players.
	Session->m_Player->coord_x = packet->coord_x;
	Session->m_Player->coord_y = packet->coord_y;
	Session->m_Player->coord_angle_z = packet->coord_angle_z;
	Session->m_Player->coord_z = packet->coord_z;
}

void SG_MMOHandler::HandleChatMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHAT_MESSAGE* packet)
{
	BM_SC_CHAT_MESSAGE_RESP response;
	BM_SC_CHAT_MESSAGE_RESP::initMessage<BM_SC_CHAT_MESSAGE_RESP>(&response);
	SG_Logger::instance().log(Session->m_Player->charname + ": " + std::string(packet->msg, packet->msg + packet->messagelength), SG_Logger::kLogLevelChat);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::EnterLobby(const boost::shared_ptr<SG_ClientSession> Session)
{
	ID_BZ_SC_ENTER_LOBBY_RESP response;
	ID_BZ_SC_ENTER_LOBBY_RESP::initMessage<ID_BZ_SC_ENTER_LOBBY_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SetSessionMessage(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_SET_SESSION_MESSAGE* packet)
{
	SG_Logger::instance().log(Session->m_Player->charname + "'s sessionmessage: " + std::string(packet->message, packet->message + 14), SG_Logger::kLogLevelMMO);
	BM_SC_SET_SESSION_MESSAGE_RESP response;
	BM_SC_SET_SESSION_MESSAGE_RESP::initMessage<BM_SC_SET_SESSION_MESSAGE_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.length = 21;
	strcpy_s(response.sessionmessage, static_cast<std::string>("Test_Session_Message").c_str());
	response.sessionmessage[20] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendMissionList(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_MISSION_LIST_RESP response;
	BM_SC_MISSION_LIST_RESP::initMessage<BM_SC_MISSION_LIST_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	response.count = static_cast<uint16_t>(Session->m_Player->missions.size());
	for (const auto &iter : Session->m_Player->missions)
	{
		response.missions.push_back(iter);
	}
	BM_SC_MISSION_LIST_RESP::recalcheader<BM_SC_MISSION_LIST_RESP>(&response);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::HandleDailyCoins(const boost::shared_ptr<SG_ClientSession> Session)
{

	//TODO: ALLOW DAILY COIN ONLY ONCE PER DAY!
	BM_SC_QUEST_DAY_COIN2_RESP response;
	BM_SC_QUEST_DAY_COIN2_RESP::initMessage<BM_SC_QUEST_DAY_COIN2_RESP>(&response);
	strcpy_s(response.message, static_cast<std::string>("ALREADY_GET_COIN").c_str());
	response.message[16] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::StartMission(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_START_MISSION_RESP response;
	BM_SC_START_MISSION_RESP::initMessage<BM_SC_START_MISSION_RESP>(&response);	
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.missionid = 55002;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::StartMinigame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MINIGAME_START* packet)
{
	BM_SC_MINIGAME_START_RESP response;
	BM_SC_MINIGAME_START_RESP::initMessage<BM_SC_MINIGAME_START_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::FinishMinigame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_MINIGAME_FINISH* packet)
{
	BM_SC_MINIGAME_FINISH_RESP response;
	BM_SC_MINIGAME_FINISH_RESP::initMessage<BM_SC_MINIGAME_FINISH_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::EnterOX(const boost::shared_ptr<SG_ClientSession> Session)
{
	Session->m_Player->IsInOX = true;
	BM_SC_MMO_OX_ENTER_RESP response;
	BM_SC_MMO_OX_ENTER_RESP::initMessage<BM_SC_MMO_OX_ENTER_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::LeaveOX(const boost::shared_ptr<SG_ClientSession> Session)
{
	Session->m_Player->IsInOX = false;
	BM_SC_MMO_OX_LEAVE_RESP response;
	BM_SC_MMO_OX_LEAVE_RESP::initMessage<BM_SC_MMO_OX_LEAVE_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SendRoomList(const boost::shared_ptr<SG_ClientSession> Session, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr)
{
	BM_SC_GET_ROOMLIST_RESP response;
	BM_SC_GET_ROOMLIST_RESP::initMessage<BM_SC_GET_ROOMLIST_RESP>(&response);
	//std::vector<sg_constructor::rooms_packet> rooms;
	//sg_constructor::rooms_packet rooms[100];
	int i = 0;
	for (const auto& iter : *roomlist_ptr)
	{
		sg_constructor::rooms_packet room;
		room.RoomID = iter->RoomID;
		strcpy_s(room.name, iter->Name.c_str());
		for (auto i = iter->Name.length(); i != 24; i++)
		{
			room.name[i] = static_cast<uint8_t>(0);
		}
		room.mode = iter->Mode;
		room.level = iter->Level;
		
		room.currentplayers = Session->m_Server->GetPlayersInRoom(iter->RoomID);
		room.maxplayers = iter->Max_Player;
		room.state = iter->State;
		response.rooms[i] = room;
		i++;
		if(i > 99)
			break;
	}
	response.roomcount = i;
	response.size = sizeof(BM_SC_GET_ROOMLIST_RESP ) + (i * sizeof(sg_constructor::rooms_packet));
	response.msg_check_sum = response.checkMessage(&response);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::RoomCreate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr, uint32_t id)
{
	if(packet->MaxPlayers > 2 || packet->MaxPlayers < 8 || packet->Level || packet->Level < 45)
	{
		//Add room to list
		boost::shared_ptr<sg_constructor::Room> RoomPtr(new sg_constructor::Room(packet->Name, packet->password, packet->Mode, packet->MaxPlayers, packet->Level, id));
		roomlist_ptr->push_back(RoomPtr);
		SG_Logger::instance().log(Session->m_Player->charname + " created room " + packet->Name, SG_Logger::kLogLevelMMO);
		
		//if (Session->m_Player->roomptr != nullptr){
		//	if (Session->m_Player->roomptr->get()->RoomID == id)
		//	{
		//		//User already joined the room for some reason
		//		BM_SC_CREATE_ROOM_ALREADYJOINED_RESP response;
		//		BM_SC_CREATE_ROOM_ALREADYJOINED_RESP::initMessage<BM_SC_CREATE_ROOM_ALREADYJOINED_RESP>(&response);
		//		strcpy_s(response.errormessage, static_cast<std::string>("ALREADY_ENTERED_ROOM").c_str());
		//		response.errormessage[20] = static_cast<uint8_t>(0);
		//		Session->SendPacketStruct(&response);
		//		return;
		//	}
		//}
			//Send successmessage
			BM_SC_CREATE_ROOM_RESP response;
			BM_SC_CREATE_ROOM_RESP::initMessage<BM_SC_CREATE_ROOM_RESP>(&response);
			strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
			response.successmessage[7] = static_cast<uint8_t>(0);
			response.roomid = RoomPtr->RoomID;
			response.relayport = Session->conf->RelayPort;
			strcpy_s(response.relayip, SG_ClientSession::conf->relayIP.c_str());
			for (auto i = SG_ClientSession::conf->relayIP.length(); i != 16; i++)
			{
				response.relayip[i] = static_cast<uint8_t>(0);
			}
			Session->SendPacketStruct(&response);
			for (const auto& iter : *roomlist_ptr)
			{
				
				if(iter->RoomID == id)
				{
					//iter->Sessions.push_back(Session);
					Session->m_Player->roomptr = iter;
				}
			}

	}else{
		//Something is wrong with the parameters
		BM_SC_CREATE_FAILED_RESP response;
		BM_SC_CREATE_FAILED_RESP::initMessage<BM_SC_CREATE_FAILED_RESP>(&response);
		strcpy_s(response.errormessage, static_cast<std::string>("INVALID_REQUEST").c_str());
		response.errormessage[15] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}

}

void SG_MMOHandler::RoomEnter(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr)
{
	for (const auto& iter : *roomlist_ptr)
	{
		if (iter->RoomID == packet->roomid +1 )
		{
			Session->m_Player->roomptr = iter;
			BM_SC_ENTER_ROOM_SUCCESS_RESP response;
			BM_SC_ENTER_ROOM_SUCCESS_RESP::initMessage<BM_SC_ENTER_ROOM_SUCCESS_RESP>(&response);
			strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
			response.successmessage[7] = static_cast<uint8_t>(0);
			response.roomid = iter->RoomID;
			response.team = 2;
			response.relayport = Session->conf->RelayPort;
			response.udpport = 5000;
			strcpy_s(response.relayip, SG_ClientSession::conf->relayIP.c_str());
			for (auto i = SG_ClientSession::conf->relayIP.length(); i != 20; i++)
			{
				response.relayip[i] = static_cast<uint8_t>(0);
			}
			Session->SendPacketStruct(&response);
			for (const auto& iter : *roomlist_ptr)
			{

				if (iter->RoomID == packet->id +1)
				{
					//iter->Sessions.push_back(Session);
					Session->m_Player->roomptr = iter;
				}
			}
			return;
		}
	}
	//Room not found, or is full or something
	BM_SC_ENTER_ROOM_FAILED_RESP response;
	BM_SC_ENTER_ROOM_FAILED_RESP::initMessage<BM_SC_ENTER_ROOM_FAILED_RESP>(&response);
	strcpy_s(response.errormessage, static_cast<std::string>("INVALID_REQUEST").c_str());
	response.errormessage[15] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::RoomLeave(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_LEAVE_ROOM_RESP response;
	BM_SC_LEAVE_ROOM_RESP::initMessage<BM_SC_LEAVE_ROOM_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::HandleMSN(const boost::shared_ptr<SG_ClientSession> Session)
{
	MM_SC_MSN_RESP response;
	MM_SC_MSN_RESP::initMessage<MM_SC_MSN_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	response.uk3 = 1;
	response.uk4 = 1;
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::FindUser(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_MSN_FIND_USER* packet)
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

void SG_MMOHandler::FriendRequest(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_FRIEND_REQUEST* packet)
{
	//TODO: Add request to database
	MM_SC_FRIEND_REQUEST_RESP response;
	MM_SC_FRIEND_REQUEST_RESP::initMessage<MM_SC_FRIEND_REQUEST_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}
void SG_MMOHandler::StartGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_START_GAME* packet)
{
	UpdateMap(Session);
	BM_SC_START_GAME_RESP response;
	BM_SC_START_GAME_RESP::initMessage<BM_SC_START_GAME_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);

}

void SG_MMOHandler::EndGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_FINISH_RACE* packet)
{
	BM_SC_END_GAME response;
	BM_SC_END_GAME::initMessage<BM_SC_END_GAME>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::SelectMap(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_SELECT_MAP* packet)
{
	if(Session->m_Player->roomptr != nullptr)
	{
		switch(packet->mapid)
		{
		case sg_constructor::sg_map::RANDOM:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::RANDOM;
			break;
		case sg_constructor::sg_map::GRIND_ROLLER:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::GRIND_ROLLER;
			break;
		case sg_constructor::sg_map::CROSS_LINK:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::CROSS_LINK;
			break;
		case sg_constructor::sg_map::GRIND_CROSS:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::GRIND_CROSS;
			break;
		case sg_constructor::sg_map::TRIESTE_EASY:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::TRIESTE_EASY;
			break;
		case sg_constructor::sg_map::ROLLER_STADIUM:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::ROLLER_STADIUM;
			break;
		case sg_constructor::sg_map::FORBIDDEN_CITY:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::FORBIDDEN_CITY;
			break;
		case sg_constructor::sg_map::STAR_TRACK:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::STAR_TRACK;
			break;
		case sg_constructor::sg_map::MIRACLE_EASY:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::MIRACLE_EASY;
			break;
		case sg_constructor::sg_map::PARAKA_EASY:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::PARAKA_EASY;
			break;
		case sg_constructor::sg_map::TRIANGLE_FARM:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::TRIANGLE_FARM;
			break;
		case sg_constructor::sg_map::LOST_ISLAND:
			Session->m_Player->roomptr->currentmap = sg_constructor::sg_map::LOST_ISLAND;
			break;
		default:
			SG_Logger::instance().log("Unknown map selected: " + packet->mapid, SG_Logger::kLogLevelMMO);
			return;
		}
	}
	UpdateMap(Session);
}

void SG_MMOHandler::UpdateMap(const boost::shared_ptr<SG_ClientSession> Session)
{
	if (Session->m_Player->roomptr != nullptr)
	{
		BM_SC_SELECT_MAP_RESP response;
		BM_SC_SELECT_MAP_RESP::initMessage<BM_SC_SELECT_MAP_RESP>(&response);
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
		response.successmessage[7] = static_cast<uint8_t>(0);
		response.mapid = Session->m_Player->roomptr->currentmap;
		Session->SendPacketStruct(&response);
	}
}


void SG_MMOHandler::UnlockDebugAccess(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_DEBUG_ACCESS response;
	BM_SC_DEBUG_ACCESS::initMessage<BM_SC_DEBUG_ACCESS>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_MMOHandler::RunClientSideScript(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_RUN_CLIENT_SIDE_SCRIPT response;
	BM_SC_RUN_CLIENT_SIDE_SCRIPT::initMessage<BM_SC_RUN_CLIENT_SIDE_SCRIPT>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}