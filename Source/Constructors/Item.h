#pragma once
#include <cstdint>

struct Item
{
	Item(){}
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