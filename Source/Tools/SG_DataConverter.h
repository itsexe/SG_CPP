#ifndef SG_DATACONVERTER
#define SG_DATACONVERTER
#pragma once

#include <cstdint>
#include <string>
#include <vector>

class SG_DataConverter
{
public:
	static void BytebufferToString(uint8_t* pData, std::size_t stSize, std::stringstream& ss);
	static void ByteToASCII(uint8_t* pData, std::size_t stSize, std::stringstream& ss);
	static std::vector<unsigned char> convertToDataArray(const unsigned char* data, int maxSize, int usedSize);
	static std::vector<unsigned char> convertToDataArray(const unsigned char* data, int size);
	void convertDataToHex(const void* data, int size, char* outHex);
	static std::vector<unsigned char> convertHexToData(const std::string& hex);
};
#endif