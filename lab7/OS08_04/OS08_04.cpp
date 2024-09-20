#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000

int main()
{
	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, L"smwTimer");
	long long it = -5 * SECOND;
	std::cout << clock() << ": main-1" << "\n";
	if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 0, NULL, NULL, FALSE)) throw "Error SetWaitableTimer";

	LPCWSTR				an = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab7\\Computer_Time\\x64\\Debug\\OS08_04x.exe";
	STARTUPINFO			si;
	PROCESS_INFORMATION	pi;
	ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);

	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		std::cout << "-- Process OS08_04x 1 created\n";
	else std::cout << "-- Process OS08_04x 1 not created\n";

	STARTUPINFO			si2;
	PROCESS_INFORMATION	pi2;
	ZeroMemory(&si2, sizeof(STARTUPINFO)); si2.cb = sizeof(STARTUPINFO);

	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		std::cout << "-- Process OS08_04x 2 created\n";
	else std::cout << "-- Process OS08_04x 2 not created\n";

	std::cout << clock() << ": main-2" << "\n";

	WaitForSingleObject(pi.hProcess, INFINITE);
	std::cout << clock() << ": OS08_04x 1" << "\n";
	if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 0, NULL, NULL, FALSE)) throw "Error SetWaitableTimer";
	WaitForSingleObject(pi2.hProcess, INFINITE);
	std::cout << clock() << ": OS08_04x 2" << "\n";
	system("pause");
	return 0;
}