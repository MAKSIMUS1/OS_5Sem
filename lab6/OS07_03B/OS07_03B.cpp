#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"smwMutex");
	if (hm == NULL) std::cout << "OS07_03B: Open Error Mutex\n";
	else std::cout << "OS07_03B: Open Mutex \n";

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30) {
			std::cout << "WaitForSingleObject OS07_03B: " << "\n";
			WaitForSingleObject(hm, INFINITE);
		}
		std::cout << "OS07_03B: " << i << "\n";

		if (i == 60) {
			ReleaseMutex(hm);
			std::cout << "ReleaseMutex OS07_03B: " << "\n";
		}
		Sleep(100);
	}
	CloseHandle(hm);

	system("pause");
	return 0;
}