#include <Windows.h>
#include <iostream>

int main()
{
	LONG prevcount = 0;
	DWORD pid = GetCurrentProcessId();
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"smwSem");
	if (hs == NULL) std::cout << "OS07_04B: Open Error Semaphore \n";
	else std::cout << "OS07_04B: Open Semaphore \n";

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30) {
			std::cout << "WaitForSingleObject OS07_03B: " << "\n";
			WaitForSingleObject(hs, INFINITE);
		}
		std::cout << pid << ": OS07_03B: " << i << "\n";

		if (i == 60) {
			ReleaseSemaphore(hs, 1, &prevcount);
			std::cout << "ReleaseMutex OS07_03B: " << "\n";
		}
		Sleep(100);
	}

	CloseHandle(hs);
	std::cout << ": OS07_04B: prevcount = " << prevcount << "\n";

	system("pause");
	return 0;
}