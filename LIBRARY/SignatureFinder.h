#pragma once

#include<Windows.h>
#include<vector>

//MASK : use x for static value & ? for dynamic value
//make sure first character is not dynamic

BOOL GetRealTimeAddressFromSignature(HANDLE ProcessHandle, LPCVOID BaseAddress, std::vector<BYTE> SignatureAdrs, char* Mask, std::vector<BYTE>& Where_you_wanna_store)
{
	BYTE Buffer[1024];
	SIZE_T BytesRead;
	bool Isfound = false;

	/*while (!Isfound)
	{
		if (!ReadProcessMemory(ProcessHandle, BaseAddress, Buffer, sizeof(Buffer), &BytesRead))
		{
			return false;
		}

		BaseAddress = reinterpret_cast<LPCVOID>(reinterpret_cast<uintptr_t>(BaseAddress) + BytesRead);

		for (int i = 0; i <= 1024 - SignatureAdrs.size(); i++)
		{
			printf("%02x ", Buffer[i]);
			if (Buffer[i] == SignatureAdrs[0])
			{
				Where_you_wanna_store.clear();
				Where_you_wanna_store.push_back(SignatureAdrs[0]);
				Isfound = true;
				for (int j = 1; j < SignatureAdrs.size(); j++)
				{
					Where_you_wanna_store.push_back(Buffer[i + j]);
					if (SignatureAdrs[j] != Buffer[i + j] && Mask[j] == 'x')
					{
						Isfound = false;
						break;
					}
				}
				if (Isfound) break;
			}
			
		}
		
	}*/

	while (!Isfound)
	{
		if (!ReadProcessMemory(ProcessHandle, BaseAddress, Buffer, sizeof(Buffer), &BytesRead))
		{
			return false;
		}

		for (int i = 0; i <= BytesRead - SignatureAdrs.size(); i++)
		{
			bool match = true;

			// Check each byte in the signature
			for (int j = 0; j < SignatureAdrs.size(); j++)
			{
				// Compare only if mask[j] is 'x'
				if (Mask[j] == 'x' && Buffer[i + j] != SignatureAdrs[j])
				{
					match = false;
					break;
				}
			}

			// If a match is found, copy the matching bytes and return
			if (match)
			{
				Where_you_wanna_store.clear();
				Where_you_wanna_store.insert(Where_you_wanna_store.end(), Buffer + i, Buffer + i + SignatureAdrs.size());
				Isfound = true;
				break;
			}
		}

		// Move to the next chunk if no match is found
		if (!Isfound)
		{
			BaseAddress = static_cast<const BYTE*>(BaseAddress) + BytesRead;
		}
	}

	return Isfound;
}