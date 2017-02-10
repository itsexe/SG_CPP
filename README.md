
# Streetgears Serveremulator
This is a emulator for the serverside the StreetGears.
StreetGears is a mmo that was discontinued mid 2012.

[![Build Status](https://travis-ci.org/itsexe/SG_CPP.svg)](https://travis-ci.org/itsexe/SG_CPP)

##Status:
Auth Server/ Login: Finished

Driving around in park town: Working, but you won't be able to see other players and most minigames won't work.

Lobbys/ Races: Partly working

Chat, Friends and stuff: Not working right now.

# How to use
If you just want to run the server, take a look at the wiki.

## Compile


### Windows:
* Install git if you haven't already (https://desktop.github.com/)
* Open a git shell (not the github desktop client)
* Download the source code of the emulator and all dependencies using: 
```
git clone --recursive https://github.com/itsexe/SG_CPP
```
* Compile boost using (This will take a some time):
```
SG_CPP\Libraries\boost\bootstrap.bat
SG_CPP\Libraries\boost\bjam --build-type=complete stage
```
* Open the SG_CPP\Source\SG_CPP.sln using visual studio and you are ready to compile the emulator

### Linux
* Install git if you haven't already
* Open a shell
* Download the source code of the emulator and all dependencies using: 
```
git clone --recursive https://github.com/itsexe/SG_CPP
```
* Run SG_CPP\Source\build.sh to compile the emulator

### macOS
* Install git if you haven't already
* Open a shell
* Download the source code of the emulator and all dependencies using: 
```
git clone --recursive https://github.com/itsexe/SG_CPP
```
* Run SG_CPP\Source\build.sh to compile the emulator

## Structure of the emulator
The client needs different kinds of servers.
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

## Contribute
Contributions are always welcome. Feel free to create pull requests (:

## Credits

* glandu2 I took some code from [his emulator for rappelz](https://github.com/glandu2/rzu~parent)
* [K1ramoX](http://www.elitepvpers.com/forum/members/4193997~k1ramox.html) and [greatmaes](https://github.com/greatmaes) for reveerseing a lot of stuff.
