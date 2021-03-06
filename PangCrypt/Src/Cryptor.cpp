#ifndef CRYPTOR_CPP
#define CRYPTOR_CPP

#include <Windows.h>
#include <stdio.h>
#include "ClientCipher.h"
#include "ServerCipher.h"
#include "DeserializeCipher.h"
#define DLLEXPORT EXTERN_C __declspec(dllexport)
typedef unsigned int uint;

//----------------- UPDATE WORK 24-12-2020 00:00:00 by LUISMK -----------------------------
//this library is a version created in C++ by LUISMK
//objective of this was to increase my learning as a programmer
//this is a remake of PangCrypt-Csharp: https://github.com/pangyatools/PangCrypt
//create by John Chadwick: https://github.com/jchv and Andreas Nedbal: https://github.com/pixeldesu
//group discord for pangYa: https://discord.gg/HwDTssf

// Decrypt pangya client packets
DLLEXPORT int pangya_client_decrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key)
{
	Utils::PrintLog(1, buffin, key, size);
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto decrypt = ClientCipher::Decrypt(packet, (int)key);
	*buffout = new unsigned char[decrypt.size()];
	*buffout = Utils::ConvertVectorToChar(decrypt);
	*buffoutSize = decrypt.size();
	return 1;
}

// Encrypt Pangya client packets, not used: packetid
DLLEXPORT int pangya_client_encrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key, char packetid)
{
	Utils::PrintLog(2, buffin, key, size);
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto encrypt = ClientCipher::Encrypt(packet, (int)key, 0);
	*buffout = new unsigned char[encrypt.size()];
	*buffout = Utils::ConvertVectorToChar(encrypt);
	*buffoutSize = encrypt.size();
	return 1;
}

// Decrypt Pangya server packets
DLLEXPORT int pangya_server_decrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key)
{
	Utils::PrintLog(3, buffin, key, size);
	unsigned char* packet_decrypt;
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto decrypt = ServerCipher::Decrypt(packet, (int)key);
	*buffout = new unsigned char[decrypt.size()];
	*buffout = Utils::ConvertVectorToChar(decrypt);
	*buffoutSize = decrypt.size();
	return 1;
}

// Encrypt Pangya server packets
DLLEXPORT int pangya_server_encrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key)
{
	Utils::PrintLog(4, buffin, key, size);
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto encrypt = ServerCipher::Encrypt(packet, (int)key, 0);
	*buffout = new unsigned char[encrypt.size()];
	*buffout = Utils::ConvertVectorToChar(encrypt);
	*buffoutSize = encrypt.size();
	return 1;
}

// This function is used to free allocated buffout
DLLEXPORT void pangya_free(char **buffout)
{
	free(*buffout);
}

//Decrypt build date client
DLLEXPORT uint pangya_deserialize(uint deserialize)
{
	return DeserializeCipher::Decrypt(deserialize);
}

//Encrypt Build date client
DLLEXPORT uint pangya_encrypt_deserialize(uint deserialize)
{
	return DeserializeCipher::Encrypt(deserialize);
}


extern "C" DLLEXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		AllocConsole();
	    freopen("CONOUT$", "w", stdout);
		string tmp;
		Utils::SetColor(1);
		Utils::ConsolePrint("=================================================================\n");
		tmp = "|                PangCrypt.dll for Pangya Emulator              |";
		tmp += "\n";
		Utils::ConsolePrint(tmp.c_str());
		tmp = "|                        PangCrypt-C++                          |";
		tmp += "\n";
		Utils::SetColor(6);
		Utils::ConsolePrint(tmp.c_str());
		Utils::SetColor(2);
		tmp = "|                        ";
		tmp += "VERSION : ";
		tmp += "20201224";
		tmp += "                     |\n";
		Utils::ConsolePrint(tmp.c_str());
		Utils::SetColor(1);
		Utils::ConsolePrint("=================================================================\n");
		Utils::SetColor(0);
		tmp = "Launched at ";
		tmp += Utils::GetDateTime();
		tmp += "\n";
		Utils::ConsolePrint(tmp.c_str());
		Utils::ConsolePrint("\n");
	}
		break;

	case DLL_PROCESS_DETACH:
		// detach from process
		break;

	case DLL_THREAD_ATTACH:
		// attach to thread
		break;

	case DLL_THREAD_DETACH:
		// detach from thread
		break;
	}
	return TRUE; // succesful
}

#endif
