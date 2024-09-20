#include <Windows.h>
#include <iostream>

int main()
{
	PROCESS_INFORMATION pi1, pi2;
	DWORD pid = GetCurrentProcessId();
	HANDLE hs = CreateSemaphore(NULL, 2, 2, L"smwSem");
	LPCWSTR anA = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab6\\Synchronization\\Debug\\OS07_04A.exe";
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(anA, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
			std::cout << "-- Process OS07_04A created\n";
		else std::cout << "-- Process OS70_04A not created\n";
	}
	LPCWSTR anB = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab6\\Synchronization\\Debug\\OS07_04B.exe";
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(anB, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
			std::cout << "-- Process OS07_04B created\n";
		else std::cout << "-- Process OS70_04B not created\n";
	}

	WaitForSingleObject(hs, INFINITE);
	for (int i = 0; i < 100; i++)
	{
		Sleep(100); std::cout << pid << ": OS07_04: " << i << "\n";
	}
	LONG prevcount = 0;
	ReleaseSemaphore(hs, 1, &prevcount);

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(hs);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}