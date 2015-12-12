#pragma once
#include <cstdint>
	struct Trickconstructor
	{
		Trickconstructor() { }
		Trickconstructor(uint64_t ID, uint32_t level, uint8_t apply) : TrickID(ID), Tricklvl(level), ApplyTrick(apply) { }

		uint32_t TrickID;
		uint32_t Tricklvl;
		uint8_t ApplyTrick;
	};
