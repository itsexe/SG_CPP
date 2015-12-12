#ifndef Config_H
#define Config_H
#pragma once
#include <cstdint>
#include <iostream>
#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/detail/ptree_implementation.hpp>

class SG_Config
	{
	public:
		const uint32_t MaxPacketSize = 1024;
		const uint32_t MinPacketSize = 5;
		const uint32_t SocketTimeout = 20000;

		const uint32_t MaxRoomCount = 100;

		const uint8_t PE_Header[16] =
		{
			0xF6, 0x23, 0x42, 0xE5,
			0xB1, 0x6A, 0xC0, 0x9F,
			0xAB, 0x46, 0xA5, 0x2D,
			0x07, 0x41, 0xD2, 0xA6
		};

		//Global config
		uint16_t MaximumUsersPerServer;

		//Database
		std::string host;
		uint16_t port;
		std::string DBUser;
		std::string DBPass;
		std::string DBName;

		//Auth configuration
		bool CheckClientVersion;
		bool CheckClientLanguage;

		//Ports
		short AuthPort;
		short MMOPort;
		short LobbyPort;
		short MsgPort;

		//IPs
		std::string AuthIP;
		
		std::string MMOIP;
		std::string LobbyIP;
		std::string msgIP;

		//Clientversion
		std::string ClientVersion;
		std::string ClientLanguage;

		//Encryption
		std::string DESPassword;
		std::string MD5Salt;

		inline void init(std::string path);
	};

void SG_Config::init(std::string path)
{
	std::fstream ifs(path); //maybe you'll have to specify your path here
	boost::property_tree::ptree conf;
	read_ini(ifs, conf);

	//Global config
	MaximumUsersPerServer = conf.get<uint16_t>("Global.MaximumUsersPerServer");

	//Database
	host = conf.get<std::string>("Database.Host");
	port = conf.get<uint16_t>("Database.Port");
	DBUser = conf.get<std::string>("Database.User");
	DBPass = conf.get<std::string>("Database.Password");
	DBName = conf.get<std::string>("Database.Database");

	//Auth configuration
	AuthIP = conf.get<std::string>("Auth.ServerIP");
	AuthPort = conf.get<short>("Auth.ServerPort");
	CheckClientVersion = conf.get<bool>("Auth.CheckVersion");
	CheckClientLanguage = conf.get<bool>("Auth.CheckLanguage");
	ClientVersion = conf.get<std::string>("Auth.ClientVersion");
	ClientLanguage = conf.get<std::string>("Auth.ClientLanguage");

	//MMO Configuration
	MMOIP = conf.get<std::string>("MMO.ServerIP");
	MMOPort = conf.get<short>("MMO.ServerPort");
	
	//Lobby Configuration
	LobbyIP = conf.get<std::string>("Lobby.ServerIP");
	LobbyPort = conf.get<short>("Lobby.ServerPort");

	//Message Configuration
	msgIP = conf.get<std::string>("Message.ServerIP");
	MsgPort = conf.get<short>("Message.ServerPort");

	//Encryption
	DESPassword = conf.get<std::string>("Encryption.DESKey");
	MD5Salt = conf.get<std::string>("Encryption.MD5Salt");
}
#endif