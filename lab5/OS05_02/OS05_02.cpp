﻿#include <Windows.h>
#include <iostream>
#include <cstdlib>

DWORD intToProcessPriority(int i);

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 4)
		{
			HANDLE processHandle = GetCurrentProcess();
			DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
			char buf[64];
			int parm1 = atoi(argv[1]);
			int parm2 = atoi(argv[2]);
			int parm3 = atoi(argv[3]);

			if (!GetProcessAffinityMask(processHandle, &pa, &sa))
				throw "Error in GetProcessAffinityMask";
			std::cout << "\t\tBefore applying parameters:\n";
			_itoa_s(pa, buf, 2);
			std::cout << "Process affinity Mask: " << buf << std::endl;
			_itoa_s(sa, buf, 2);
			std::cout << "System affinity Mask:  " << buf << std::endl;

			if (!SetProcessAffinityMask(processHandle, parm1))
				throw "ERROR in SetProcessAffinityMask";
			if (!GetProcessAffinityMask(processHandle, &pa, &sa))
				throw "Error in GetProcessAffinityMask";

			std::cout << "\t\tAfter applying parameters:\n";
			_itoa_s(pa, buf, 2);
			std::cout << "Process affinity Mask: " << buf << std::endl;
			_itoa_s(sa, buf, 2);
			std::cout << "System affinity Mask:  " << buf << std::endl;

			_itoa_s(parm1, buf, 2);
			std::cout << "Child 1 PriorityClass: " << parm2 << std::endl;
			std::cout << "Child 2 PriorityClass: " << parm3 << std::endl;

			LPCWSTR path1 = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab5\\x64\\Debug\\OS05_02x.exe";
			LPCWSTR path2 = L"D:\\BSTU\\Kurs_3_1\\OS(Pilinoga)\\lab5\\x64\\Debug\\OS05_02x.exe";

			STARTUPINFO si1, si2;
			PROCESS_INFORMATION pi1, pi2;

			ZeroMemory(&si1, sizeof(STARTUPINFO));
			ZeroMemory(&si2, sizeof(STARTUPINFO));
			si1.cb = sizeof(STARTUPINFO);
			si2.cb = sizeof(STARTUPINFO);

			if (CreateProcess(path1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | intToProcessPriority(parm2), NULL, NULL, &si1, &pi1))
				std::cout << "-- Process os05_02 1 was created\n";
			else std::cout << "-- Process os05_02 1 wasn't created\n";

			if (CreateProcess(path2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | intToProcessPriority(parm3), NULL, NULL, &si2, &pi2))
				std::cout << "-- Process OS05_02 2 was created\n";
			else std::cout << "-- Process OS05_02 2 wasn't created\n";

			WaitForSingleObject(pi1.hProcess, INFINITE);
			WaitForSingleObject(pi2.hProcess, INFINITE);

			CloseHandle(pi1.hProcess);
			CloseHandle(pi2.hProcess);
		}
		else
			std::cout << "No parameters provided" << std::endl;
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}
	system("pause");
}

DWORD intToProcessPriority(int i) {
	switch (i)
	{
	case 1: return IDLE_PRIORITY_CLASS;
	case 2: return BELOW_NORMAL_PRIORITY_CLASS;
	case 3: return NORMAL_PRIORITY_CLASS;
	case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
	case 5: return HIGH_PRIORITY_CLASS;
	case 6: return REALTIME_PRIORITY_CLASS;
	default: throw "Unknown priority class";
	}
}
