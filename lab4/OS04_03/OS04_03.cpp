#include <iostream>
#include <Windows.h>
#include <thread>

DWORD pid = NULL;

DWORD WINAPI OS04_03_T1()
{
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; i++) {
        std::cout << "PID = " << pid << ", OS04_03_T1 Thread: " << "tid-" << tid << ": " << i << "\n";
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI OS04_03_T2()
{
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 125; i++) {
        std::cout << "PID = " << pid << ", OS04_03_T2 Thread: " << "tid-" << tid << ": " << i << "\n";
        Sleep(1000);
    }
    return 0;
}

int main()
{
    pid = GetCurrentProcessId();

    DWORD tid = GetCurrentThreadId();
    DWORD T1Id = NULL;
    HANDLE hT1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_03_T1, NULL, 0, &T1Id);
    Sleep(200);

    DWORD T2Id = NULL;
    HANDLE hT2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_03_T2, NULL, 0, &T2Id);
    Sleep(200);

    for (int i = 0; i < 100; i++)
    {
        std::cout << "PID = " << pid << ", Main Thread: " << "tid-" << tid << ": " << i << "\n";
        if (i == 5) {
            SuspendThread(hT1);
            std::cout << "Suspend OS04_03_T1 \n";
        }
        if (i == 7) {
            SuspendThread(hT2);
            std::cout << "Suspend OS04_03_T2 \n";
        }
        if (i == 12) {
            ResumeThread(hT1);
            std::cout << "Resume OS04_03_T1 \n";
        }
        Sleep(1000);
    }
    ResumeThread(hT1);
    std::cout << "Resume OS04_03_T2 \n";

    WaitForSingleObject(hT1, INFINITE);
    WaitForSingleObject(hT2, INFINITE);

    CloseHandle(hT1);
    CloseHandle(hT2);

    system("pause");
    return 0;
}