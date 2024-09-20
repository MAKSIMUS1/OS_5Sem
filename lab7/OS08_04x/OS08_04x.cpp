#include <Windows.h>
#include <iostream>
#include <ctime>

bool flag = true;

int simple_true(int n) 
{
	int i, sq;
	if (n % 2 == 0) { return 0; }
	sq = (int)sqrt(n);
	for (i = 3; i <= sq; i++) {
		if ((n % i) == 0) { return 0; }
	}
	return 1;
}

DWORD WINAPI ChildThread()
{
	int n = 1;
	while (flag)
	{
		if (simple_true(n)) { printf("%d ", n); }
		n++;
		Sleep(200);
	}
	return 0;
}

int main()
{
	int n = 1;
	std::cout << clock() << ": OS08_04x-1 \n";
	HANDLE htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"smwTimer");

	DWORD ChildId = 0;
	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, NULL, &ChildId);

	WaitForSingleObject(htimer, INFINITE);
	flag = false;
	WaitForSingleObject(hChild, INFINITE);

	std::cout << clock() << ": OS08_04x-2 \n";
	system("pause");
	return 0;
}

