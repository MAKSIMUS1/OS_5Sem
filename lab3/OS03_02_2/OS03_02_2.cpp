#include <windows.h>
#include <iostream>

int main(void)
{
	for (int i = 0; i < 125; i++)
	{
		std::cout << GetCurrentProcessId() << std::endl;
		Sleep(1000);
	}
	return 0;
}