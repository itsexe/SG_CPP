#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <fstream>

#include <detours.h>
#pragma comment(lib, "detours.lib")

std::ofstream ofstrFile;

int32_t __cdecl hEncryptMessage(uint32_t hashtable_ptr, uint32_t from_Buffer, uint32_t to_Buffer, uint32_t Size)
{
	uint32_t hashtable_ptr_old = hashtable_ptr;
	uint32_t Hashtable_1 = *(uint32_t*)hashtable_ptr;
	uint32_t Hashtable_2 = *(uint32_t*)(hashtable_ptr + 4);

	for (auto i = 0; i != Size; ++i)
	{
		Hashtable_1 = (uint8_t)(Hashtable_1 + 1);
		char tmpKey_1 = *(BYTE *)(hashtable_ptr + Hashtable_1 + 8);

		Hashtable_2 = (uint8_t)(tmpKey_1 + Hashtable_2);
		char tmpKey_2 = *(uint8_t *)(hashtable_ptr + Hashtable_2 + 8);

		*(uint8_t *)(hashtable_ptr + Hashtable_1 + 8) = tmpKey_2;
		*(uint8_t *)(hashtable_ptr + Hashtable_2 + 8) = tmpKey_1;

		*(uint8_t *)(to_Buffer + i) = *(uint8_t *)(from_Buffer + i);
	}

	*(DWORD *)hashtable_ptr = Hashtable_1;
	*(DWORD *)(hashtable_ptr + 4) = Hashtable_2;

	return hashtable_ptr_old;
}

void WINAPI hOutputDebugStringA(LPCTSTR lpOutputString)
{
	std::cout << lpOutputString;
	ofstrFile << lpOutputString;
	ofstrFile.flush();
}

void Patch()
{
	DetourFunction((uint8_t*)0x007B25A0, (uint8_t*)hEncryptMessage); // remove packet encryption [SEND]
	//DetourFunction((uint8_t*)0x00440D2F, (uint8_t*)0x00440D43); // remove password encryption
	DetourFunction((uint8_t*)0x00443500, (uint8_t*)0x00443528); // remove game guard init
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		Patch();

	return TRUE;
}