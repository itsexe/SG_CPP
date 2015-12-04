#ifndef Config_H
#define Config_H
#pragma once
#include <cstdint>
#include <iostream>
#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/detail/ptree_implementation.hpp>

namespace SG_Config
	{
		static const uint32_t MaxPacketSize = 1024;
		static const uint32_t MinPacketSize = 5;
		static const uint32_t SocketTimeout = 20000;

		static const uint32_t MaxRoomCount = 100;

		const uint8_t PE_Header[16] =
		{
			0xF6, 0x23, 0x42, 0xE5,
			0xB1, 0x6A, 0xC0, 0x9F,
			0xAB, 0x46, 0xA5, 0x2D,
			0x07, 0x41, 0xD2, 0xA6
		};

		//Global config
		static uint16_t MaximumUsersPerServer;

		//Database
		static std::string host;
		static uint16_t port;
		static std::string DBUser;
		static std::string DBPass;
		static std::string DBName;

		//Auth configuration
		static bool CheckClientVersion;
		static bool CheckClientLanguage;

		//Ports
		static short AuthPort;
		static short MMOPort;
		static short LobbyPort;
		static short MsgPort;

		//IPs
		static std::string AuthIP;
		static std::string MMOIP;
		static std::string LobbyIP;
		static std::string MsgIP;

		//Clientversion
		static std::string ClientVersion;
		static std::string ClientLanguage{

		};

		//Encryption
		static std::string DESPassword;
		static std::string MD5Salt;

		static inline void init();
	};

void SG_Config::init()
{
	boost::property_tree::ptree conf;
	read_ini("C:\\Users\\Simon\\Documents\\Visual Studio 2015\\Projects\\SG_Auth\\Debug\\SG_Config.ini", conf);

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
	MsgIP = conf.get<std::string>("Message.ServerIP");
	MsgPort = conf.get<short>("Message.ServerPort");

	//Encryption
	DESPassword = conf.get<std::string>("Encryption.DESKey");
	MD5Salt = conf.get<std::string>("Encryption.MD5Salt");
}
#endif