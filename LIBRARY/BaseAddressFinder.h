#pragma once

#include<Windows.h>
#include<TlHelp32.h>
#include<iostream>

LPCVOID GetBaseAddress(DWORD ProcessID, const char* ModuleName) {
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
	if (SnapShot == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to get snapshot\n";
		exit(0);
	}

	LPCVOID FinalBaseAddress = nullptr;
	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);

	// Iterate through the modules and print each name
	if (Module32First(SnapShot, &me32)) {
		do {
			//std::wcout << L"Module Name: " << me32.szModule << L" at Base Address: " << me32.modBaseAddr << std::endl;
			if (strcmp(ModuleName, me32.szModule) == 0) {
				FinalBaseAddress = me32.modBaseAddr;  // Get the base address
				break;
			}
		} while (Module32Next(SnapShot, &me32));
	}
	else {
		std::cout << "Module32First failed with error: " << GetLastError() << std::endl;
	}

	CloseHandle(SnapShot);
	return FinalBaseAddress;
}
