#include <iostream>
#include <cstdlib>
#include "Windows.h"

void printProcessPrty(HANDLE h);
void printThreadPrty(HANDLE h);
DWORD intToProcessPriority(int i);
DWORD intToThreadPriority(int i);


void childThread()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);

	for (int i = 0; i < 1000000; i++)
	{
		if (i % 1000 == 0)
		{
			std::cout << "------------------------------------------\n";
			std::cout << "Iteration: " << i << std::endl;
			std::cout << "PID: " << pid << "\nTID: " << tid << std::endl;
			printProcessPrty(hp);
			printThreadPrty(ht);
			std::cout << "Thread IdealProcessor: " << std::dec << icpu << "\n\n";
			Sleep(200);
		}
	}
	return;
}


int main(int argc, char* argv[])
{
	try
	{
		if (argc == 5)
		{
			HANDLE processHandle = GetCurrentProcess();
			DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
			char buf[64];
			int parm1 = atoi(argv[1]);
			int parm2 = atoi(argv[2]);
			int parm3 = atoi(argv[3]);
			int parm4 = atoi(argv[4]);

			if (!GetProcessAffinityMask(processHandle, &pa, &sa)) throw "Error in GetProcessAffinityMask";
			std::cout << "\t\tBefore applying parameters:\n";
			_itoa_s(pa, buf, 2);
			std::cout << "Process affinity Mask: " << buf << std::endl;
			_itoa_s(sa, buf, 2);
			std::cout << "System affinity Mask: " << buf << std::endl;

			if (!SetProcessAffinityMask(processHandle, parm1)) throw "ERROR in SetProcessAffinityMask";

			if (!GetProcessAffinityMask(processHandle, &pa, &sa)) throw "Error in GetProcessAffinityMask";
			std::cout << "\t\tAfter applying parameters:\n";
			_itoa_s(pa, buf, 2);
			std::cout << "Process affinity Mask: " << buf << std::endl;
			_itoa_s(sa, buf, 2);
			std::cout << "System affinity Mask: " << buf << std::endl;

			SetPriorityClass(processHandle, intToProcessPriority(parm2));
			std::cout << "Main PriorityClass: " << parm2 << std::endl;

			DWORD childId_T1, childId_T2 = NULL;
			HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)childThread, NULL, CREATE_SUSPENDED, &childId_T1);
			HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)childThread, NULL, CREATE_SUSPENDED, &childId_T2);

			SetThreadPriority(hChild1, intToThreadPriority(parm3));
			SetThreadPriority(hChild2, intToThreadPriority(parm4));

			printThreadPrty(hChild1);
			printThreadPrty(hChild2);

			ResumeThread(hChild1);
			ResumeThread(hChild2);

			WaitForSingleObject(hChild1, INFINITE);
			WaitForSingleObject(hChild2, INFINITE);

			CloseHandle(hChild1);
			CloseHandle(hChild2);
		}
		else std::cout << "No parameters provided" << std::endl;
	}
	catch (std::string err) {
		std::cout << err << std::endl;
	}
	system("pause");
}

void printProcessPrty(HANDLE h)
{
	DWORD prty = GetPriorityClass(h);	//приоритет процесса
	std::cout << " ---- Current PID = " << GetCurrentProcessId() << " \n";
	switch (prty)
	{
	case IDLE_PRIORITY_CLASS:			std::cout << " ----+ priority = IDLE_PRIORITY_CLASS \n";			break;
	case BELOW_NORMAL_PRIORITY_CLASS:	std::cout << " ----+ priority = BELOW_NORMAL_PRIORITY_CLASS \n";	break;
	case NORMAL_PRIORITY_CLASS:			std::cout << " ----+ priority = NORMAL_PRIORITY_CLASS \n";			break;
	case ABOVE_NORMAL_PRIORITY_CLASS:	std::cout << " ----+ priority = ABOVE_NORMAL_PRIORITY_CLASS \n";	break;
	case HIGH_PRIORITY_CLASS:			std::cout << " ----+ priority = HIGH_PRIORITY_CLASS \n";			break;
	case REALTIME_PRIORITY_CLASS:		std::cout << " ----+ priority = REALTIME_PRIORITY_CLASS \n";		break;
	default: std::cout << " ----+ priority = ? \n";
	}
	return;
}

void printThreadPrty(HANDLE h)
{
	DWORD prty = GetThreadPriority(h);	//приоритет потока
	std::cout << " ---- Current Thread ID = " << GetCurrentThreadId() << " \n";
	switch (prty)
	{
	case THREAD_PRIORITY_LOWEST:		std::cout << " ----+ priority = THREAD_PRIORITY_LOWEST \n";			break;
	case THREAD_PRIORITY_BELOW_NORMAL:	std::cout << " ----+ priority = THREAD_PRIORITY_BELOW_NORMAL \n";	break;
	case THREAD_PRIORITY_NORMAL:		std::cout << " ----+ priority = THREAD_PRIORITY_NORMAL \n";			break;
	case THREAD_PRIORITY_ABOVE_NORMAL:	std::cout << " ----+ priority = THREAD_PRIORITY_ABOVE_NORMAL \n";	break;
	case THREAD_PRIORITY_HIGHEST:		std::cout << " ----+ priority = THREAD_PRIORITY_HIGHEST \n";		break;
	case THREAD_PRIORITY_IDLE:			std::cout << " ----+ priority = THREAD_PRIORITY_IDLE \n";			break;
	case THREAD_PRIORITY_TIME_CRITICAL:	std::cout << " ----+ priority = THREAD_PRIORITY_TIME_CRITICAL \n";	break;
	default: std::cout << " ----+ priority = ? \n";
	}
	return;
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

DWORD intToThreadPriority(int i)
{
	switch (i)
	{
	case 1: return THREAD_PRIORITY_LOWEST;
	case 2: return THREAD_PRIORITY_BELOW_NORMAL;
	case 3: return THREAD_PRIORITY_NORMAL;
	case 4: return THREAD_PRIORITY_ABOVE_NORMAL;
	case 5: return THREAD_PRIORITY_HIGHEST;
	case 6: return THREAD_PRIORITY_IDLE;
	default: throw "No such priority class";
	}
}
