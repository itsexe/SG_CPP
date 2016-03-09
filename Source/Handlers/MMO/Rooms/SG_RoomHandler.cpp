#include "SG_RoomHandler.h"
#include <Tools/SG_Logger.h>
#include <Networking/General/SG_ClientSession.h>
#include <Networking/General/SG_ServerBase.h>

void SG_RoomHandler::SendRoomList(const boost::shared_ptr<SG_ClientSession> Session, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr)
{

	std::vector<sg_constructor::rooms_packet> rooms;
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
		rooms.push_back(room);
	}
	BM_SC_GET_ROOMLIST_RESP *response;
	response = TS_MESSAGE_WNA::create<BM_SC_GET_ROOMLIST_RESP, sg_constructor::rooms_packet>(Session->m_Server->Rooms_internal.size());
	response->roomcount = static_cast<uint16_t>(rooms.size());
	int i = 0;
	for (const auto& iter : rooms)
	{
		response->rooms[i] = iter;
		i++;
	}
	Session->SendPacketStruct(response);
}

void SG_RoomHandler::RoomCreate(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CREATE_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr, uint32_t id)
{
	if (packet->MaxPlayers > 2 || packet->MaxPlayers < 8 || packet->Level || packet->Level < 45)
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
		response.udpport = 5000;
		strcpy_s(response.relayip, SG_ClientSession::conf->relayIP.c_str());
		for (auto i = SG_ClientSession::conf->relayIP.length(); i != 20; i++)
		{
			response.relayip[i] = static_cast<uint8_t>(0);
		}
		Session->SendPacketStruct(&response);
		for (const auto& iter : *roomlist_ptr)
		{

			if (iter->RoomID == id)
			{
				//iter->Sessions.push_back(Session);
				Session->m_Player->roomptr = iter;
			}
		}

	}
	else {
		//Something is wrong with the parameters
		BM_SC_CREATE_FAILED_RESP response;
		BM_SC_CREATE_FAILED_RESP::initMessage<BM_SC_CREATE_FAILED_RESP>(&response);
		strcpy_s(response.errormessage, static_cast<std::string>("INVALID_REQUEST").c_str());
		response.errormessage[15] = static_cast<uint8_t>(0);
		Session->SendPacketStruct(&response);
	}

}

void SG_RoomHandler::RoomEnter(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_ENTER_ROOM* packet, std::list<boost::shared_ptr<sg_constructor::Room>>* roomlist_ptr)
{
	for (const auto& iter : *roomlist_ptr)
	{
		if (iter->RoomID == packet->roomid + 1)
		{
			Session->m_Player->roomptr = iter;
			Session->m_Player->IsReady = 0;
			BM_SC_ENTER_ROOM_SUCCESS_RESP response;
			BM_SC_ENTER_ROOM_SUCCESS_RESP::initMessage<BM_SC_ENTER_ROOM_SUCCESS_RESP>(&response);
			strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
			response.successmessage[7] = static_cast<uint8_t>(0);
			//response.roomid = iter->RoomID;
			response.team = 0;
			response.relayport = Session->conf->RelayPort;
			response.udpport = 5000;
			strcpy_s(response.relayip, SG_ClientSession::conf->relayIP.c_str());
			for (auto i = SG_ClientSession::conf->relayIP.length(); i != 20; i++)
			{
				response.relayip[i] = static_cast<uint8_t>(0);
			}
			Session->SendPacketStruct(&response);
			for (const auto& iter2 : *roomlist_ptr)
			{
				if (iter2->RoomID == packet->roomid + 1)
				{
					Session->m_Player->roomptr = iter2;
				}
			}

			//inform other players about the new room member
			BM_SC_ROOM_MULTI_INFO_RESP response2 = GeneratePlayerRoomUpdate(Session, 1, true);
			Session->m_Server->SendRoomBroadcast(&response2, Session->m_Player->roomptr->RoomID, Session);

			uint8_t position = 2;
			//inform new player about current players
			for (const auto& iter2 : Session->m_Server->Sessions)
			{
				if (iter2->m_Player->roomptr != nullptr)
				{
					if (iter2->m_Player->roomptr->RoomID == packet->roomid + 1)
					{
						BM_SC_ROOM_MULTI_INFO_RESP response3 = GeneratePlayerRoomUpdate(iter2, position);
						Session->SendPacketStruct(&response3);
						position++;
					}
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

void SG_RoomHandler::RoomLeave(const boost::shared_ptr<SG_ClientSession> Session)
{
	BM_SC_LEAVE_ROOM_RESP response;
	BM_SC_LEAVE_ROOM_RESP::initMessage<BM_SC_LEAVE_ROOM_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
	Session->m_Player->roomptr.reset();
}

void SG_RoomHandler::HandlePlayerReady(const boost::shared_ptr<SG_ClientSession> Session)
{
	if (Session->m_Player->IsReady == 1)
		Session->m_Player->IsReady = 0;
	else
		Session->m_Player->IsReady = 1;
	BM_SC_READY_GAME_RESP response;
	BM_SC_READY_GAME_RESP::initMessage<BM_SC_READY_GAME_RESP>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
	BM_SC_ROOM_MULTI_INFO_RESP response2 = GeneratePlayerRoomUpdate(Session, Session->m_Player->RoomPosition);
	Session->SendPacketStruct(&response2);
	Session->m_Server->SendRoomBroadcast(&response2, Session->m_Player->roomptr->RoomID, Session, true);
}

void SG_RoomHandler::HandlePlayerRoomInfo(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CHARACTER_INFO* packet)
{
	//This is a long ass packet.
	//there is a lot of stuff wich needs to be outsourced to the database or something

	std::string charname(packet->charname, packet->charname + 40);
	charname = std::string(charname.c_str());
	for (const auto& iter : Session->m_Server->Sessions)
	{
		if (iter->m_Player->charname == charname)
		{
			BM_SC_CHARACTER_INFO_RESP response;
			BM_SC_CHARACTER_INFO_RESP::initMessage<BM_SC_CHARACTER_INFO_RESP>(&response);
			strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
			response.successmessage[7] = static_cast<uint8_t>(0);
			response.uk1 = 1;
			response.uk2 = 2;
			response.uk3 = 3;
			response.uk4 = 4;
			strcpy_s(response.charname, static_cast<std::string>(iter->m_Player->charname).c_str());
			for (auto i = iter->m_Player->charname.length(); i != 40; ++i)
			{
				response.charname[i] = static_cast<uint8_t>(0);
			}
			response.uk5 = 5;
			response.uk6 = 6;
			response.uk7 = 7;
			response.chartype = iter->m_Player->chartype;
			response.uk8 = 53;
			response.uk9 = 8;
			response.uk10 = 40;
			response.uk11 = 10;
			response.uk12 = 39;
			response.uk13 = 11;
			response.uk14 = 14;
			response.uk15 = 15;
			response.uk16 = 16;
			response.charlevel = static_cast<uint32_t>(iter->m_Player->charlevel);
			response.uk17 = 18;
			response.uk18 = 19;
			response.uk19 = 20;
			response.uk20 = 21;
			response.uk21 = 22;

			response.head = iter->m_Player->head;
			response.face = iter->m_Player->face;
			response.upper = iter->m_Player->upper;
			response.lower = iter->m_Player->lower;
			response.foot = iter->m_Player->foot;
			response.hand = iter->m_Player->hand;
			response.google = iter->m_Player->google;
			response.accesoire = iter->m_Player->accesoire;
			response.theme = iter->m_Player->theme;
			response.mantle = iter->m_Player->mantle;
			response.buckle = iter->m_Player->buckle;
			response.vent = iter->m_Player->vent;
			response.nitro = iter->m_Player->nitro;
			response.wheels = iter->m_Player->wheels;

			response.uk22 = 37;
			response.uk23 = 38;

			response.tricksize = 13;
			for (auto i = 0; i != 12; ++i)
			{
				response.tricklist[i] = sg_constructor::Tricksrace(iter->m_Player->tricks[i].TrickID, 0);
			}
			Session->SendPacketStruct(&response);
			break;
		}
	}
}


void SG_RoomHandler::StartGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_START_GAME* packet)
{
	UpdateMap(Session);
	std::vector<sg_constructor::room_players> playerlist;
	uint16_t IDx = 100;
	for (const auto& iter : Session->m_Server->Sessions)
	{
		if (iter->m_Player->roomptr != nullptr)
		{
			if (iter->m_Player->roomptr->RoomID == Session->m_Player->roomptr->RoomID)
			{
				IDx++;
				sg_constructor::room_players player;
				strcpy_s(player.charname, static_cast<std::string>(iter->m_Player->charname).c_str());
				strcpy_s(player.remoteendpoint, iter->getSocket().remote_endpoint().address().to_string().c_str());
				for (auto i = iter->m_Player->charname.length(); i != 40; ++i)
				{
					player.charname[i] = static_cast<uint8_t>(0);
				}
				for (auto i = iter->getSocket().remote_endpoint().address().to_string().length(); i != 16; ++i)
				{
					player.remoteendpoint[i] = static_cast<uint8_t>(0);
				}
				player.uk10 = 16;
				player.uk11 = 1;
				player.uk12 = 1;
				player.index_p = IDx;
				if (IDx == 101)
					player.ismaster = 1;
				else
					player.ismaster = 0;
				playerlist.push_back(player);
			}
		}
	}
	BM_SC_START_GAME_RESP *response;
	response = TS_MESSAGE_WNA::create<BM_SC_START_GAME_RESP, sg_constructor::room_players>(playerlist.size());
	strcpy_s(response->successmessage, static_cast<std::string>("SUCCESS").c_str());
	strcpy_s(response->encryptionkey, static_cast<std::string>("encryptionbla<3").c_str());
	response->successmessage[7] = static_cast<uint8_t>(0);
	response->encryptionkey[15] = static_cast<uint8_t>(0);
	response->uk1 = 0;
	response->uk2 = 0;
	response->playercount = static_cast<uint16_t>(playerlist.size());
	int i = 0;
	for (const auto& iter : playerlist)
	{
		response->players[i] = iter;
		i++;
	}
	Session->m_Server->SendRoomBroadcast(response, Session->m_Player->roomptr->RoomID, Session, true);
}

void SG_RoomHandler::EndGame(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_FINISH_RACE* packet)
{
	BM_SC_END_GAME response;
	BM_SC_END_GAME::initMessage<BM_SC_END_GAME>(&response);
	strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
	response.successmessage[7] = static_cast<uint8_t>(0);
	Session->SendPacketStruct(&response);
}

void SG_RoomHandler::SelectMap(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_SELECT_MAP* packet)
{
	int mapList[11]{
		sg_constructor::sg_map::GRIND_ROLLER,
		sg_constructor::sg_map::CROSS_LINK,
		sg_constructor::sg_map::GRIND_CROSS,
		sg_constructor::sg_map::TRIESTE_EASY,
		sg_constructor::sg_map::ROLLER_STADIUM,
		sg_constructor::sg_map::FORBIDDEN_CITY,
		sg_constructor::sg_map::STAR_TRACK,
		sg_constructor::sg_map::MIRACLE_EASY,
		sg_constructor::sg_map::PARAKA_EASY,
		sg_constructor::sg_map::TRIANGLE_FARM,
		sg_constructor::sg_map::LOST_ISLAND };
	if (Session->m_Player->roomptr != nullptr)
	{
		if (packet->mapid == sg_constructor::sg_map::RANDOM)
			Session->m_Player->roomptr->currentmap = static_cast<sg_constructor::sg_map>(mapList[rand() % 11]);
		else
			Session->m_Player->roomptr->currentmap = static_cast<sg_constructor::sg_map>(packet->mapid);
	}
	UpdateMap(Session);
}

void SG_RoomHandler::UpdateMap(const boost::shared_ptr<SG_ClientSession> Session)
{
	if (Session->m_Player->roomptr != nullptr)
	{
		BM_SC_SELECT_MAP_RESP response;
		BM_SC_SELECT_MAP_RESP::initMessage<BM_SC_SELECT_MAP_RESP>(&response);
		strcpy_s(response.successmessage, static_cast<std::string>("SUCCESS").c_str());
		response.successmessage[7] = static_cast<uint8_t>(0);
		response.mapid = Session->m_Player->roomptr->currentmap;
		//Send to everyone in the room
		Session->m_Server->SendRoomBroadcast(&response, Session->m_Player->roomptr->RoomID, Session, true);


		BM_SC_MAP_INFO_RESP response2;
		BM_SC_MAP_INFO_RESP::initMessage<BM_SC_MAP_INFO_RESP>(&response2);
		//strcpy_s(response2.successmessage, static_cast<std::string>("SUCCESS").c_str());
		//response2.successmessage[7] = static_cast<uint8_t>(0);
		response2.mapid = Session->m_Player->roomptr->currentmap;
		Session->m_Server->SendRoomBroadcast(&response2, Session->m_Player->roomptr->RoomID, Session, true);
	}
}

void SG_RoomHandler::HandleUnknownInfo(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_UNKNOWN_INFO* packet)
{
	BM_SC_UNKNOWN_INFO_RESP response;
	BM_SC_UNKNOWN_INFO_RESP::initMessage<BM_SC_UNKNOWN_INFO_RESP>(&response);
	strcpy_s(response.name, static_cast<std::string>("irgendwastest").c_str());
	for (auto i = static_cast<std::string>("irgendwastest").length(); i != 33; ++i)
	{
		response.name[i] = static_cast<uint8_t>(0);
	}
	Session->SendPacketStruct(&response);
}

BM_SC_ROOM_MULTI_INFO_RESP &SG_RoomHandler::GeneratePlayerRoomUpdate(const boost::shared_ptr<SG_ClientSession> Session, uint8_t position, bool newplayer)
{
	BM_SC_ROOM_MULTI_INFO_RESP response;
	BM_SC_ROOM_MULTI_INFO_RESP::initMessage<BM_SC_ROOM_MULTI_INFO_RESP>(&response);
	strcpy_s(response.remoteendpoint, static_cast<std::string>(Session->getSocket().remote_endpoint().address().to_string()).c_str());
	for (auto i = Session->getSocket().remote_endpoint().address().to_string().length(); i != 33; ++i)
	{
		response.remoteendpoint[i] = static_cast<uint8_t>(0);
	}
	strcpy_s(response.charname, static_cast<std::string>(Session->m_Player->charname).c_str());
	for (auto i = Session->m_Player->charname.length(); i != 40; ++i)
	{
		response.charname[i] = static_cast<uint8_t>(0);
	}
	response.slotdisplay = position;
	response.chartype = Session->m_Player->chartype;
	response.ready = Session->m_Player->IsReady;
	if (newplayer == true)
		response.enterinfo = 3;
	else
		response.enterinfo = 0;
	if (Session->m_Player->rank > 1)
		response.isadmin = 1;

	response.slotdisplay = position;
	response.uk1 = 0;
	response.uk2 = 0;
	response.uk3 = 1;
	Session->m_Player->RoomPosition = position;
	return response;
}