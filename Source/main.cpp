#include <iostream>
#include "Networking/Auth/SG_AuthServer.h"
#include "Networking/MMO/SG_MmoServer.h"
#include "Tools/Database/Database.h"

#include "tools/SG_Logger.h"
#include "SG_Config.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Networking/Lobby/SG_LobbyServer.h"

int main()
{
	int option;
	std::cout << "Please select the Server" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "1.	Auth" << std::endl;
	std::cout << "2.	MMO" << std::endl;
	std::cout << "3.	Lobby" << std::endl;
	std::cout << "99.	All in one" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << ">> ";
	std::cin >> option;

#ifdef _WIN32
	std::system("cls"); // For Windows
#else
	std::system("clear"); //For Linux, Mac, Whatever
#endif

	boost::shared_ptr<SG_AuthServer> pAuth(new SG_AuthServer());
	boost::shared_ptr<SG_MmoServer> pMMO(new SG_MmoServer());
	boost::shared_ptr<SG_LobbyServer> pLobby(new SG_LobbyServer());
	boost::shared_ptr<MySQLConnection> pDatabase(new MySQLConnection());
	SG_Config::init();
	pDatabase->Connect(SG_Config::host, SG_Config::port, SG_Config::DBUser, SG_Config::DBPass, SG_Config::DBName);
	SG_ClientSession::SQLConn = pDatabase.get();

	switch(option)
	{
	case 1:
		pAuth->InitServer(SG_Config::AuthIP, SG_Config::AuthPort, 1);
		SG_Logger::instance().log("Auth Server started", SG_Logger::kLogLevelInfo);
		break;
	case 2:
		pMMO->InitServer(SG_Config::MMOIP, SG_Config::MMOPort, 1);
		SG_Logger::instance().log("MMO Server started", SG_Logger::kLogLevelInfo);
		break;
	case 3:
		pLobby->InitServer(SG_Config::LobbyIP, SG_Config::LobbyPort, 1);
		SG_Logger::instance().log("Lobby Server started", SG_Logger::kLogLevelInfo);
		break;
	case 99:
		pAuth->InitServer(SG_Config::AuthIP, SG_Config::AuthPort, 1);
		SG_Logger::instance().log("Auth Server started", SG_Logger::kLogLevelInfo);
		pMMO->InitServer(SG_Config::MMOIP, SG_Config::MMOPort, 1);
		SG_Logger::instance().log("MMO Server started", SG_Logger::kLogLevelInfo);
		pLobby->InitServer(SG_Config::LobbyIP, SG_Config::LobbyPort, 1);
		SG_Logger::instance().log("Lobby Server started", SG_Logger::kLogLevelInfo);
		break;
	default:
		std::cout << std::endl << "INVALID SERVER" << std::endl;
		break;
	}
	while(1)
	{
		std::cin.get();
	}
}