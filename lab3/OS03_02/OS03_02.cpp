#include <Windows.h>
#include <iostream>

int main()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;

	std::wstring ApplicationName1(L"OS03_02_1.exe");
	LPWSTR AppName1 = &ApplicationName1[0];

	if (CreateProcess(AppName1, NULL,
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &cif, &pi) == TRUE)
	{
		std::cout << "process" << std::endl;
		std::wcout << "handle " << pi.hProcess << std::endl;
	}

	std::wstring ApplicationName2(L"OS03_02_2.exe");
	LPWSTR AppName2 = &ApplicationName2[0];

	if (CreateProcess(AppName2, NULL,
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &cif, &pi) == TRUE)
	{
		std::cout << "process" << std::endl;
		std::wcout << "handle " << pi.hProcess << std::endl;
	}

	for (int i = 0; i < 100; i++)
	{
		std::cout << GetCurrentProcessId() << std::endl;
		Sleep(1000);
	}

	system("pause");
	return 0;
}