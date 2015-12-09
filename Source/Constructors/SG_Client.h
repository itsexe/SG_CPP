#ifndef SG_CLIENT
#define SG_CLIENT
#pragma once
#include <string>
#include <vector>
#include "Trick.h"
#include "Item.h"

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
	std::vector<Trickconstructor> tricks;
	std::vector<Item> items;

	uint32_t gpotatos;
	uint32_t coins;
	uint32_t rupees;
	uint32_t questpoints;

	//Positionstuff
	float coord_x;
	float coord_y;
	float coord_angle_z;
	float coord_z;

	//Quiz
	bool IsInOX = false;


private:
	const std::string strChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

};

#endif