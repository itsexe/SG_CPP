#ifndef SG_CLIENT
#define SG_CLIENT
#pragma once
#include <string>

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

private:
	const std::string strChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

};

#endif