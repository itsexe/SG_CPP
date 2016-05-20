#include "SG_DataConverter.h"
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

void SG_DataConverter::BytebufferToString(uint8_t* pData, std::size_t stSize, std::stringstream& ss)
{
	for (auto i = 0; i != stSize; ++i)
	{
		ss << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << static_cast<int32_t>(pData[i]) << " ";
	}
}
void SG_DataConverter::ByteToASCII(uint8_t* pData, std::size_t stSize, std::stringstream& ss)
{
	for (auto i = 0; i != stSize; ++i)
	{
		if (*static_cast<uint8_t*>(pData + i) < 32 || *static_cast<uint8_t*>(pData + i) > 176)
		{
			ss << ".";
		}
		else
		{
			ss << *reinterpret_cast<char*>(pData) + i;
		}
	}
}
std::vector<unsigned char> SG_DataConverter::convertToDataArray(const unsigned char *data, int maxSize, int usedSize) {
	return std::vector<unsigned char>(data, data + std::max(0, std::min(maxSize, usedSize)));
}
std::vector<unsigned char> SG_DataConverter::convertToDataArray(const unsigned char *data, int size) {
	return std::vector<unsigned char>(data, data + size);
}

void SG_DataConverter::convertDataToHex(const void *data, int size, char *outHex) {
	static const char hexMapping[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	int i;
	for (i = 0; i < size; i++) {
		outHex[i * 2] = hexMapping[static_cast<const char*>(data)[i] >> 4];
		outHex[i * 2 + 1] = hexMapping[static_cast<const char*>(data)[i] & 0x0F];
	}
	outHex[i * 2] = '\0';
}

std::vector<unsigned char> SG_DataConverter::convertHexToData(const std::string &hex) {
	size_t i;
	size_t size = hex.size() / 2;
	std::vector<unsigned char> result;

	result.reserve(size);

	for (i = 0; i < size; i++) {
		unsigned char c = hex[i * 2];
		unsigned char val = 0;

		if (c >= '0' && c <= '9')
			val = (c - '0') << 4;
		else if (c >= 'A' && c <= 'F')
			val = (c - 'A' + 10) << 4;
		else if (c >= 'a' && c <= 'f')
			val = (c - 'a' + 10) << 4;

		c = hex[i * 2 + 1];

		if (c >= '0' && c <= '9')
			val |= (c - '0');
		else if (c >= 'A' && c <= 'F')
			val |= c - 'A' + 10;
		else if (c >= 'a' && c <= 'f')
			val |= c - 'a' + 10;

		result.push_back(val);
	}

	return result;
}