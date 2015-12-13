
# Streetgears Serveremulator
This is a emulator for the serverside the StreetGears.
StreetGears is a mmo that was discontinued mid 2012.
[![Build Status](https://travis-ci.org/itsexe/SG_CPP.svg)](https://travis-ci.org/itsexe/SG_CPP)

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


## Setup
Please take a look at the wiki!

## Contribute
Contributions are always welcome. Feel free to create pull requests (:

## Credits

* glandu2 I took some code from [his emulator for rappelz](https://github.com/glandu2/rzu~parent)
* [K1ramoX](http://www.elitepvpers.com/forum/members/4193997~k1ramox.html) and [greatmaes](https://github.com/greatmaes) for reveerseing a lot of stuff.
