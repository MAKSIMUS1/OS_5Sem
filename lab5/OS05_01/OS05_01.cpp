#include <Windows.h>
#include <intrin.h>
#include <iostream>
#include <iomanip>
#include <bitset>

void printProcessPrty(HANDLE h);
void printThreadPrty(HANDLE h);

int main()
{
	HANDLE hp = GetCurrentProcess();	// текущий процесс
	HANDLE ht = GetCurrentThread();		// текуший поток

	printProcessPrty(hp);
	printThreadPrty(ht);

	try
	{
		{
			DWORD_PTR pa = NULL, sa = NULL;
			DWORD icpu = -1;
			if (!GetProcessAffinityMask(hp, &pa, &sa)) throw "GetProcessAffinityMask";
			std::cout << "Process	affinity Mask: " << std::showbase << std::bitset<16>{pa} << "\n";
			std::cout << "System	affinity Mask: " << std::showbase << std::bitset<16>{sa} << "\n";

			SYSTEM_INFO si;
			GetSystemInfo(&si);
			std::cout << "Количество процессоров доступных  процессу: " << std::dec << si.dwNumberOfProcessors << "\n";
			icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);

			std::cout << "Thread Ideal Processor: " << std::dec << icpu << "\n";
		}
		std::cout << "\n\n";
	}
	catch (char* msg) { std::cout << "Error: " << msg << "\n"; }

	std::cout << "\n\n";
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