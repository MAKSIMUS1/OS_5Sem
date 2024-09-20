#include <Windows.h>
#include <intrin.h>
#include <iostream>
#include <iomanip>
#include <bitset>

void printProcessPrty(HANDLE h);
void printThreadPrty(HANDLE h);

void PrintAffinityMask(HANDLE hp, HANDLE ht) {
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
	char buf[64];

	if (!GetProcessAffinityMask(hp, &pa, &sa))
		throw "[FATAL] GetProcessAffinityMask threw an exception.";

	_itoa_s(pa, buf, 2);
	std::cout << "Process affinity mask: " << buf;
	std::cout << " (" << std::showbase << std::hex << pa << ")\n";
	_itoa_s(sa, buf, 2);
	std::cout << "System affinity mask:  " << buf;
	std::cout << " (" << std::showbase << std::hex << sa << ")\n";


	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	//cout << "Max processors count:  " << dec << sys_info.dwNumberOfProcessors << "\n";
	icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	std::cout << "Thread IdealProcessor: " << std::dec << icpu << "\n";
}




int main()
{
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();


	for (int i = 0; i < 1000000; i++)
	{
		if (i % 1000 == 0)
		{
			std::cout << "\n--------------------------------------------\n\n";
			std::cout << "Iteration:         " << i << "\n\n";
			std::cout << "Current PID:       " << pid << "\n";
			std::cout << "Current TID:       " << tid << "\n";
			printProcessPrty(processHandle);
			printThreadPrty(threadHandle);
			std::cout << "\n";
			PrintAffinityMask(processHandle, threadHandle);
			std::cout << "\n--------------------------------------------\n\n\n";
			Sleep(200);
		}
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