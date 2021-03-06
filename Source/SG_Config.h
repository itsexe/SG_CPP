#ifndef Config_H
#define Config_H
#pragma once
#include <cstdint>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Tools/SG_Logger.h"
#include <boost/filesystem.hpp>

class SG_Config
	{
	public:
		static const uint32_t MaxPacketSize = 1024;
		static const uint32_t MinPacketSize = 5;
		static const uint32_t SocketTimeout = 20000;

		static const uint32_t MaxRoomCount = 100;

		//Global config
		uint16_t MaximumUsersPerServer;
		std::string ExternalIP;

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
		short RelayPort;

		//IPs
		std::string AuthIP;
		
		std::string MMOIP;
		std::string LobbyIP;
		std::string msgIP;
		std::string relayIP;

		//Clientversion
		std::string ClientVersion;
		std::string ClientLanguage;

		//Encryption
		std::string DESPassword;
		std::string MD5Salt;

		inline void init(std::string path);

	private:
		static inline void CreateMissingConfigFile(std::string name);
	};

inline void SG_Config::CreateMissingConfigFile(std::string name)
{
	std::ofstream outfile(name);
	outfile << "[Global]" << std::endl;
	outfile << "MaximumUsersPerServer=1000" << std::endl;
	outfile << "ExternalIP=127.0.0.1" << std::endl;
	outfile << "[Database]" << std::endl;
	outfile << "Host=127.0.0.1" << std::endl << "Port = 3306" << std::endl << "User=root" << std::endl << "Password=" << std::endl << "Database=sg" << std::endl;
	outfile << "[Auth]" << std::endl;
	outfile << "ServerIP=127.0.0.1" << std::endl << "ServerPort=1337" << std::endl << "CheckVersion=0" << std::endl << "CheckLanguage=0" << std::endl << "ClientVersion=200708240" << std::endl << "ClientLanguage=fr" << std::endl;
	outfile << "[MMO]" << std::endl;
	outfile << "ServerIP=127.0.0.1" << std::endl << "ServerPort=1338" << std::endl;
	outfile << "[Lobby]" << std::endl;
	outfile << "ServerIP=127.0.0.1" << std::endl << "ServerPort=1339" << std::endl;
	outfile << "[Message]" << std::endl;
	outfile << "ServerIP=127.0.0.1" << std::endl << "ServerPort=1340" << std::endl;
	outfile << "[Relay]" << std::endl;
	outfile << "ServerIP=127.0.0.1" << std::endl << "ServerPort=1341" << std::endl;
	outfile << "[Encryption]" << std::endl;
	outfile << "DESKey=!_a^Rc* | #][Ych$~'(M _!d4aUo^%${T!~}h*&X%" << std::endl << "MD5Salt=" << std::endl;
}

void SG_Config::init(std::string path)
{
	if(!boost::filesystem::exists(path))
	{
		SG_Logger::instance().log("Config file not found in: " + path + ". Creating config file. Everything is set to default, please check the file to customize emulator.", SG_Logger::kLogLevelError);
		SG_Config::CreateMissingConfigFile(path);
	}
	try
	{
		std::fstream ifs(path); //maybe you'll have to specify your path here
		boost::property_tree::ptree conf;
		read_ini(ifs, conf);

		//Global config
		MaximumUsersPerServer = conf.get<uint16_t>("Global.MaximumUsersPerServer");
		ExternalIP = conf.get<std::string>("Global.ExternalIP");

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

		//Message Configuration
		relayIP = conf.get<std::string>("Relay.ServerIP");
		RelayPort = conf.get<short>("Relay.ServerPort");

		//Encryption
		DESPassword = conf.get<std::string>("Encryption.DESKey");
		MD5Salt = conf.get<std::string>("Encryption.MD5Salt");
	}catch(boost::property_tree::ini_parser_error &e)
	{
		SG_Logger::instance().log("Something is wrong with your config! Error occured in: " + e.filename() + ":" + std::to_string(e.line()) + " Errormessage: " + e.message() + ". Press any key to exit.", SG_Logger::kLogLevelError);
		getchar();
		exit(-2);
	}
	catch(...){
		SG_Logger::instance().log("Something is wrong with your config! Press any key to exit.", SG_Logger::kLogLevelError);
		getchar();
		exit(-3);
	}
}
#endif