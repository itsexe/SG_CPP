apt-get install libmysqlclient-dev libboost-all-dev libssl-dev

rm -rf out/
mkdir out/
g++ -c main.cpp -std=c++11 -o main.o -I .
g++ -c Networking/Lobby/SG_LobbyServer.cpp -std=c++11 -o SG_LobbyServer.o -I .
g++ -c Handlers/Lobby/SG_LobbyHandler.cpp -std=c++11 -o SG_LobbyHandler.o -I .
g++ -c Tools/Database/Database.cpp -std=c++11 -o Database.o -I .
g++ -c Handlers/MMO/SG_MMOHandler.cpp -std=c++11 -o SG_MMOHandler.o -I .
g++ -c Networking/MMO/SG_MmoServer.cpp -std=c++11 -o SG_MmoServer.o -I .
g++ -c Tools/Encryption/DesPasswordCipher.cpp -std=c++11 -o DesPasswordCipher.o -I .
g++ -c Handlers/Auth/SG_AuthHandler.cpp -std=c++11 -o SG_AuthHandler.o -I .
g++ -c Constructors/SG_Client.cpp -std=c++11 -o SG_Client.o -I .
g++ -c Networking/General/SG_ClientSession.cpp -std=c++11 -o SG_ClientSession.o -I .
g++ -c Tools/SG_DataConverter.cpp -std=c++11 -o SG_DataConverter.o -I .
g++ -c Tools/SG_Logger.cpp -std=c++11 -o SG_Logger.o -I .
g++ -c Networking/General/SG_ServerBase.cpp -std=c++11 -o SG_ServerBase.o -I .
g++ -c Handlers/Relay/SG_RelayHandler.cpp -std=c++11 -o SG_RelayHandler.o -I .
g++ -c Networking/Relay/SG_RelayServer.cpp -std=c++11 -o SG_RelayServer.o -I .
g++ -c Handlers/MMO/Social/SG_ChatHandler.cpp -std=c++11 -o SG_ChatHandler.o -I .
g++ -c Handlers/MMO/Minigames/OX/SG_QuizHandler.cpp -std=c++11 -o SG_QuizHandler.o -I .
g++ -c Handlers/MMO/Rooms/SG_RoomHandler.cpp -std=c++11 -o SG_RoomHandler.o -I .
g++ -c Handlers/MMO/Social/SG_SocialHandler.cpp -std=c++11 -o SG_SocialHandler.o -I .
g++ -c Handlers/MMO/Minigames/SG_MinigameHandler.cpp -std=c++11 -o SG_MinigameHandler.o -I .
g++ -c Networking/Message/SG_MessageServer.cpp -std=c++11 -o SG_MessageServer.o -I .
g++ -c Tools/Encryption/RC4Cipher.cpp -std=c++11 -o RC4Cipher.o -I .

g++ main.o SG_LobbyServer.o SG_LobbyHandler.o Database.o SG_MMOHandler.o SG_MmoServer.o DesPasswordCipher.o SG_AuthHandler.o SG_Client.o SG_ClientSession.o SG_DataConverter.o SG_Logger.o SG_ServerBase.o SG_RelayHandler.o SG_RelayServer.o SG_QuizHandler.o SG_ChatHandler.o SG_RoomHandler.o SG_SocialHandler.o SG_MinigameHandler.o SG_MessageServer.o RC4Cipher.o -lboost_system -lboost_filesystem -lboost_thread -lpthread -lmysqlclient -lcrypto