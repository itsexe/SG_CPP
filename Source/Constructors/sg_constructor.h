#pragma once
#include <cinttypes>
#include <string>

namespace sg_constructor
{
	enum sg_map : uint16_t
	{
		RANDOM = 0,
		GRIND_ROLLER = 57,
		CROSS_LINK = 59,
		GRIND_CROSS = 61,
		TRIESTE_EASY = 119,
		ROLLER_STADIUM = 67,
		FORBIDDEN_CITY = 107,
		STAR_TRACK = 63,
		MIRACLE_EASY = 120,
		PARAKA_EASY = 121,
		TRIANGLE_FARM = 122,
		LOST_ISLAND = 123,
	};
	struct Item
	{
		Item() {}
		Item(uint32_t Unique, uint32_t ID, uint32_t trade, uint32_t Dura, uint16_t uk2, uint8_t equip, uint32_t uk4)
			: UniqueID(Unique), ItemID(ID), Trade_Status(trade), Duration(Dura), uk_2(uk2), Equip_Status(equip), uk_4(uk4) { }
		//	Item ID; Itemtype ID; Handelbar; Verbleibende Zeit; Angelegt; ?;

		uint32_t UniqueID;
		uint32_t ItemID;
		uint32_t Trade_Status; // 0 = No | 1 = Yes
		uint16_t uk1;
		uint32_t Duration;
		uint32_t uk2;
		uint16_t uk_2;
		uint8_t Equip_Status; // 0 = No | 1 = Yes
		uint32_t uk_4;
	};
	struct Trickconstructor
	{
		Trickconstructor() { }
		Trickconstructor(uint32_t ID, uint32_t level, uint8_t apply) : TrickID(ID), Tricklvl(level), ApplyTrick(apply) { }

		uint32_t TrickID;
		uint32_t Tricklvl;
		uint8_t ApplyTrick;
	};
	struct Tricksrace
	{
		Tricksrace() { }
		Tricksrace(uint32_t ID, uint32_t level) : TrickID(ID), uk1(level) { }

		uint32_t uk1;
		uint32_t TrickID;
	};
	struct Room //internal room structure
	{
		Room(){}
		Room(std::string name, std::string pw, uint32_t mode, uint8_t max_player, uint8_t level, uint32_t RoomID)
			: Name(name), Password(pw), Mode(mode), Max_Player(max_player), Level(level),  State (1), RoomID(RoomID), currentmap(sg_map::RANDOM) { }

		uint32_t RoomID;
		std::string Name;
		std::string Password;

		// 0/1 = free item-mode	| 2/3 = password item-mode
		// 4/5 = free speed-mode	| 6/7 = password speed-mode
		uint32_t Mode;
		uint8_t Max_Player;
		uint8_t State; // enter state -> 0 = can enter | 1 = no enter
		uint8_t Level; // level -> 0 = all | 1 = anfaenger | 2 = profi | 3 = profi II | 4 = meister | 5 = superstar
		sg_map currentmap;
	};
	struct rooms_packet //This will be sent as a packet
	{
		rooms_packet(){}
		rooms_packet(uint32_t _roomid, std::string _name, uint32_t _mode, uint8_t _currentplayers, uint8_t _maxplayers, uint8_t _state, uint8_t _level) : RoomID(_roomid), mode(_mode), currentplayers(_currentplayers), maxplayers(_maxplayers), state(_state), level(_level){}


		uint32_t RoomID;
		char name[24];
		uint32_t mode;
		uint8_t currentplayers;
		uint8_t maxplayers;
		uint8_t state;
		uint8_t level;
	};
}