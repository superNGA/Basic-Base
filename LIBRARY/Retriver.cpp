#include"Retriver.h"

std::vector<HWND> Retriver::Handle_Allprok;
std::vector<std::string> Retriver::AllName;

void Retriver::execute(HWND* HWND_STORAGE, DWORD* PROCESS_ID_STORAGE, HANDLE* HANDLE_STORAGE, std::string* Name)
{
	Handle_Allprok.clear();
	AllName.clear();

	EnumWindows(Allprok, 0);

	int choice;
	std::cout << "Select the process : \n";
	for (int i = 0; i < Handle_Allprok.size(); i++)
	{
		std::cout << i + 1 << ". HWND : " << Handle_Allprok[i] << " | Title : " << AllName[i] << "\n";
	}
	std::cout << "-->  ";
	std::cin >> choice;
	std::cout << std::endl;

	system("cls");

	HWND Myhandle = Handle_Allprok[choice - 1];
	DWORD Process_ID;
	if (!GetWindowThreadProcessId(Myhandle, &Process_ID))
	{
		std::cout << "Failed to get Process Id\n";
		return;
	}
	HANDLE Process_Handle = OpenProcess(PROCESS_VM_READ, NULL, Process_ID);
	if (Process_Handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to get handle to process\n";
		return;
	}

	(*HWND_STORAGE) = Myhandle;
	(*PROCESS_ID_STORAGE) = Process_ID;
	(*HANDLE_STORAGE) = Process_Handle;
	(*Name) = AllName[choice - 1];

	return;
}

BOOL CALLBACK Retriver::Allprok(HWND grabber, LPARAM LParam)
{
	char Title[256];
	GetWindowTextA(grabber, Title, sizeof(Title));
	if (IsWindowVisible(grabber) && strlen(Title) > 0)
	{
		AllName.push_back(Title);
		Handle_Allprok.push_back(grabber);
	}
	return TRUE;
}