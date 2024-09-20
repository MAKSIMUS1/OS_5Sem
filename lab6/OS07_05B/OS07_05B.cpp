#include <Windows.h>
#include <iostream>

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"smwEvent");
	if (he == NULL) std::cout << "OS07_05B: Open Error Event \n";
	else std::cout << "OS07_05B: Open Event \n";

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i <= 90; ++i)
	{
		std::cout << pid << ": OS07_05B: " << i << "\n";
		Sleep(100);
	}

	CloseHandle(he);
	system("pause");
	return 0;
}