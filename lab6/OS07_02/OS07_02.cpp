#include <Windows.h>
#include <iostream>

HANDLE createThread(LPTHREAD_START_ROUTINE func, char* thread_name)
{
	DWORD thread_id = NULL;
	HANDLE thread = CreateThread(NULL, 0, func, thread_name, 0, &thread_id);
	if (thread == NULL)
		throw "[ERROR] CreateThread";
	return thread;
}

DWORD pid = NULL;
DWORD WINAPI ChildThread(char* displayed_name);

CRITICAL_SECTION cs;

int main()
{
	pid = GetCurrentProcessId();

	DWORD tid = GetCurrentThreadId();
	const int size = 2;
	HANDLE threads[size];

	threads[0] = createThread((LPTHREAD_START_ROUTINE)ChildThread, (char*)"A");
	threads[1] = createThread((LPTHREAD_START_ROUTINE)ChildThread, (char*)"B");

	InitializeCriticalSection(&cs);

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30) {
			std::cout << "Main\t" << "tid-" << tid << " Enter Crititcal Section" << "\n";
			EnterCriticalSection(&cs);
		}
		std::cout << "Main\t" << "PID = " << pid << ", Parent Thread: " << "tid-" << tid << ": " << i << "\n";

		if (i == 60) {
			std::cout << "Main\t" << "tid-" << tid << " Leave Crititcal Section" << "\n";
			LeaveCriticalSection(&cs);
		}


		Sleep(100);
	}

	WaitForMultipleObjects(size, threads, TRUE, INFINITE);
	DeleteCriticalSection(&cs);

	for (int i = 0; i < size; i++)
		CloseHandle(threads[i]);
	return 0;
}

DWORD WINAPI ChildThread(char* displayed_name)
{
	DWORD tid = GetCurrentThreadId();

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30) {
			std::cout << "tid-" << tid << " Enter Crititcal Section" << "\n";
			EnterCriticalSection(&cs);
		}

		std::cout << displayed_name  << "\tPID = " << pid << ", Child Thread: " << "tid-" << tid << ": " << i << "\n";

		if (i == 60) {
			std::cout << "tid-" << tid << " Leave Crititcal Section" << "\n";
			LeaveCriticalSection(&cs);
		}

		Sleep(100);
	}

	std::cout << "\n==========================  " << displayed_name << " finished" << "  ==========================\n\n";

	return 0;
}