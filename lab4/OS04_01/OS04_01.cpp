#include <iostream>
#include <windows.h>

int main()
{
    std::cout << "Process Id: " << GetCurrentProcessId() << std::endl;
    std::cout << "Thread Id: " << GetCurrentThreadId() << std::endl;   
}