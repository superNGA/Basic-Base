#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
#include<vector>

class Retriver
{
public:
	void execute(HWND* HWND_STORAGE, DWORD* PROCESS_ID_STORAGE, HANDLE* HANDLE_STORAGE, std::string* Name);
private:
	static BOOL CALLBACK Allprok(HWND grabber, LPARAM LParam);
	static std::vector<HWND> Handle_Allprok;
	static std::vector<std::string> AllName;
};




