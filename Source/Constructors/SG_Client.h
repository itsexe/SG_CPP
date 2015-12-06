#ifndef SG_CLIENT
#define SG_CLIENT
#pragma once
#include <string>
#include <vector>
#include "Trick.h"

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
	std::string charname;
	uint16_t firstlogin;
	uint32_t chartype;
	uint64_t charlevel;
	std::vector<Trickconstructor> tricks;

	uint32_t gpotatos;
	uint32_t coins;
	uint32_t rupees;
	uint32_t questpoints;
private:
	const std::string strChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

};

#endif