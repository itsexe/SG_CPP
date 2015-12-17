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
	std::string charname;
	uint16_t charcreated;
	uint32_t chartype;
	uint64_t charlevel;

	std::vector<uint64_t> missions;
	sg_constructor::Trickconstructor tricks[13];
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
	boost::shared_ptr<sg_constructor::Room> roomptr;

private:
	std::string strChars;

};

#endif