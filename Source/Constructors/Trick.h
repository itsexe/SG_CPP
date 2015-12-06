#pragma once
#include <cstdint>
	struct Trickconstructor
	{
		Trickconstructor(){ }
		Trickconstructor(uint64_t ID, uint8_t uk_Flag) : TrickID(ID), unknown_flag(uk_Flag) { }

		uint64_t TrickID;
		uint8_t unknown_flag;
	};
