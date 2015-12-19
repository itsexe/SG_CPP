#include <iostream>
#include "Networking/Auth/SG_AuthServer.h"
#include "Networking/MMO/SG_MmoServer.h"
#include "Networking/Lobby/SG_LobbyServer.h"
#include "Networking/Relay/SG_RelayServer.h"

#include "Tools/Database/Database.h"

#include "Tools/SG_Logger.h"
#include "SG_Config.h"
#include <boost/smart_ptr/shared_ptr.hpp>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <Config path>" << std::endl;
		return 1;
	}
	int option;
	std::cout << "Please select the Server" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "1.	Auth" << std::endl;
	std::cout << "2.	MMO" << std::endl;
	std::cout << "3.	Lobby" << std::endl;
	std::cout << "4.	Relay" << std::endl;
	std::cout << "99.	All in one" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << ">> ";
#ifdef _WIN32
	if (IsDebuggerPresent())
	{
		option = 99;
	}
	else
	{
		std::cin >> option;
	}
	std::system("cls"); // For Windows
#else
	std::system("clear"); //For Linux, Mac, Whatever
#endif

	boost::shared_ptr<SG_AuthServer> pAuth(new SG_AuthServer());
	boost::shared_ptr<SG_MmoServer> pMMO(new SG_MmoServer());
	boost::shared_ptr<SG_LobbyServer> pLobby(new SG_LobbyServer());
	boost::shared_ptr<SG_RelayServer> pRelay(new SG_RelayServer());
	boost::shared_ptr<MySQLConnection> pDatabase(new MySQLConnection());
	boost::shared_ptr<SG_Config> conf(new SG_Config());
	conf->init(argv[1]);
	pDatabase->Connect(conf->host, conf->port, conf->DBUser, conf->DBPass, conf->DBName);
	SG_ClientSession::SQLConn = pDatabase.get();
	SG_ClientSession::conf = conf.get();
	switch(option)
	{
	case 1:
		pAuth->InitServer(conf->AuthIP, conf->AuthPort, 1);
		SG_Logger::instance().log("Auth Server started", SG_Logger::kLogLevelInfo);
		break;
	case 2:
		pMMO->InitServer(conf->MMOIP, conf->MMOPort, 1);
		SG_Logger::instance().log("MMO Server started", SG_Logger::kLogLevelInfo);
		break;
	case 3:
		pLobby->InitServer(conf->LobbyIP, conf->LobbyPort, 1);
		SG_Logger::instance().log("Lobby Server started", SG_Logger::kLogLevelInfo);
		break;
	case 4:
		pRelay->InitServer(conf->relayIP, conf->RelayPort, 1);
		SG_Logger::instance().log("Relay Server started", SG_Logger::kLogLevelInfo);
		break;
	case 99:
		pAuth->InitServer(conf->AuthIP, conf->AuthPort, 1);
		SG_Logger::instance().log("Auth Server started", SG_Logger::kLogLevelInfo);
		pMMO->InitServer(conf->MMOIP, conf->MMOPort, 1);
		SG_Logger::instance().log("MMO Server started", SG_Logger::kLogLevelInfo);
		pLobby->InitServer(conf->LobbyIP, conf->LobbyPort, 1);
		SG_Logger::instance().log("Lobby Server started", SG_Logger::kLogLevelInfo);
		pRelay->InitServer(conf->relayIP, conf->RelayPort, 1);
		SG_Logger::instance().log("Relay Server started", SG_Logger::kLogLevelInfo);
		break;
	default:
		std::cout << std::endl << "INVALID NUMBER" << std::endl;
		break;
	}
	while(1)
	{
		std::cin.get();
	}
}