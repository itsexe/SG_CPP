
# Streetgears Serveremulator
This is a emulator for the serverside the StreetGears.
StreetGears is a mmo that was discontinued mid 2012.

Please note:
This is a very early stage of development.
The only thing that works in most parts is the loginserver.

## State of the Emulator
Auth Server: (80%)

MMO Server (0%)

Lobby Server: (0%)

Message Server: (0%)

## Structure of the emulator
The emulator has diffrent types to servers.
### Auth Server
The Auth Server handles the basic authentification.
It has following tasks:
* Checking username and password
* Checking the clientversion and language
* Assigning sessionkeys
* Sending the list of servers to the client

### MMO Server
The MMO Server handels everything in Parktown.
Some of his tasks:
* Sending more detailed player info than the Auth Server (Charstats, Clothing, Balanceinfo etc.)
* Social stuff (Chat, friends, etc.)
* Sending positions of other players
* Minigames
* and much more

### Lobby Server
The Lobby server handles the rooms and initializes the races. Although the races are P2P.

## Packets

### Commuication between Server and Client
The packets are pretty simple. The server serializes them using structs. This way we will get a clean and easy to understand code.
Every packet has the same header. The structure of the header looks like this:
```
struct TS~MESSAGE
{
uint16~t size;
uint16~t packetID;
uint8~t hash;
};
```
After we serialized the header, we will detect the packetID and serialize the packet again with the full structure.
The full structure is always a extention to the base structure (TS~MESSAGE) and will look like this:
```
struct TS~CA~VERSION : public TS~MESSAGE
{
char szVersion[20];
char szLang[3];
static const uint16~t packetID = 1003;
};
```
(The packet in this example is used to check the clientversion and the language).
We will also use this method to create the packets we send to the client.

### Commuication between Servers
All servers will register themself at the Database Server.
To simplify matters they use the same packet headers as the client.


## Setup
### How to compile
Since this is a cross plattform project, i only included the cmake files.
#### Depencencies
This project needs some external libraries.
* Boost Version 1.59.0 (You can get it at http://www.boost.org/or if you use Linux "sudo apt~get install libboost~all~dev")
* OpenSSL (http://slproweb.com/products/Win32OpenSSL.html)
* CMake (https://cmake.org/download/#latest)

### Setup server
At the moment the settings are hardcoded. (Will be moved to a ini file soon!)
If you want to change the ports or MySQL~Connectionstrings you can do it in "SG~Config.h".

#### Config File
```
[Global]
MaximumUsersPerServer=1000
[Database]
Host=DATABASE HOST
Port=DATABASE PORT
User=DATABASE USER
Password=YOUR-SQL-PASSWORD
Database=DATABASENAME
[Auth]
ServerIP=127.0.0.1
ServerPort=1800
CheckVersion=0
CheckLanguage=0
ClientVersion=200708240
ClientLanguage=de
[MMO]
ServerIP=127.0.0.1
ServerPort=1801
[Lobby]
ServerIP=127.0.0.1
ServerPort=1802
[Message]
ServerIP=127.0.0.1
ServerPort=1803
[Encryption]
DESKey=!_a^Rc* | #][Ych$~'(M _!d4aUo^%${T!~}h*&X%
MD5Salt=irgendwas
```

### Setup client
If you want to start the client in german you can use following arguments:
```
StreetGear.exe /enc /locale:cp1141 /auth~ip:127.0.0.1 /auth~port:1337 /window /debug /log
```
To start it in french use:
```
StreetGear.exe /enc /locale:cp1147 /auth~ip:127.0.0.1 /auth~port:1337 /window /debug /log
```
(Apparently there is also a korean Version. To start the game in korean use "/locale:cp949")

Before you login, you have to inject the DebugLibrary to disable the packetencryption.

## Contribute
Contributions are always welcome. Feel free to create pull requests (:

## Credits

* glandu2 I took some code from [his emulator for rappelz](https://github.com/glandu2/rzu~parent)
* [K1ramoX](http://www.elitepvpers.com/forum/members/4193997~k1ramox.html) and [greatmaes](https://github.com/greatmaes) for reveerseing a lot of stuff.
