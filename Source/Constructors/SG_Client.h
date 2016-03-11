#ifndef SG_CLIENT
#define SG_CLIENT
#pragma once
#include <string>
#include <vector>
#include "sg_constructor.h"
#include <boost/smart_ptr/shared_ptr.hpp>

class SG_Client
{
public:
	SG_Client();
	void UpdateLastKeepAlive();
	
	std::string SessionKey;
	time_t LastKeepAlive;

	//Client Settings
	std::string ClientVersion;
	std::string ClientLang;

	//Session Settings
	std::string Username;
	std::string Password;
	unsigned char CryptedPassword[19];

	//Playersettings
	uint16_t playerid;
	uint16_t charid;
	std::string charname;
	uint16_t charcreated;
	uint32_t chartype;
	uint64_t charlevel;
	uint32_t zoneid;
	uint8_t age;
	std::string zoneinfo;
	std::string biostr;
	uint8_t gender; // 1 = Male; 2 = Female; (Todo: Maybe add other options if this isn't hardcoded)
	uint8_t isprivate; // Display infos to all players

	//look
	uint32_t head;
	uint32_t face;
	uint32_t upper;
	uint32_t lower;
	uint32_t foot;
	uint32_t hand;
	uint32_t google;
	uint32_t accesoire;
	uint32_t theme;
	uint32_t mantle;
	uint32_t buckle;
	uint32_t vent;
	uint32_t nitro;
	uint32_t wheels;

	//Tricks
	uint8_t grind; //max 5
	uint8_t backflip; //max 4
	uint8_t frontflip; //max 5
	uint8_t airtwist; //max 5
	uint8_t powerswing; //max 4
	uint8_t gripturn; //max 3
	uint8_t dash; //max 3
	uint8_t backskating; //max 3
	uint8_t jumpingsteer; //max 3
	uint8_t butting; //max 5
	uint8_t powerslide; //max 0
	uint8_t powerjump; //max 3
	uint8_t wallride; //max 4

	std::vector<uint64_t> missions;
	std::vector<sg_constructor::Trickconstructor> tricks;
	std::vector<sg_constructor::Item> items;

	uint32_t gpotatos;
	uint32_t coins;
	uint32_t rupees;
	uint32_t questpoints;

	uint32_t exp;
	uint32_t license;

	uint8_t rank; // 0 = normal user, 1 = Mod, 2 = GM, 3 = Dev

	//Positionstuff
	float coord_x;
	float coord_y;
	float coord_angle_z;
	float coord_z;

	//Quiz
	bool IsInOX;

	time_t LastBonusCoin;


	//Rooms_internal
	bool IsInRoom;
	bool IsReady;
	uint8_t RoomPosition;
	boost::shared_ptr<sg_constructor::Room> roomptr;

private:
	std::string strChars;

};

#endif