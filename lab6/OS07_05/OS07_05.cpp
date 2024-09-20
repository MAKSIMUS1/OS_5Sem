#include <Windows.h>
#include <iostream>

int main()
{
	PROCESS_INFORMATION pi1, pi2;
	DWORD pid = GetCurrentProcessId();
	HANDLE he = CreateEvent(NULL, TRUE, FALSE, L"smwEvent");
	LPCWSTR anA = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab6\\Synchronization\\Debug\\OS07_05A.exe";
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(anA, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
			std::cout << "-- Process OS07_05A created\n";
		else std::cout << "-- Process OS70_05A not created\n";
	}
	LPCWSTR anB = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab6\\Synchronization\\Debug\\OS07_05B.exe";
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(anB, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
			std::cout << "-- Process OS07_05B created\n";
		else std::cout << "-- Process OS70_05B not created\n";
	}

	for (int i = 1; i <= 90; i++)
	{
		if(i == 15)
			PulseEvent(he);
		Sleep(300); std::cout << pid << ": OS07_05: " << i << "\n";
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(he);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}