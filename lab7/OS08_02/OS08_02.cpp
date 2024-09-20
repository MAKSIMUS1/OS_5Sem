#include <Windows.h>
#include <iostream>
#include <ctime>

int main()
{
	unsigned long long i = 0;
	clock_t t1 = clock();
	bool flag = false;

	while (true)
	{
		i++;
		
		if (((clock() - t1) / CLOCKS_PER_SEC) == 5 && !flag) {
			std::cout << i << "\n";
			flag = true;
		}
		if (((clock() - t1) / CLOCKS_PER_SEC) == 10 && flag) {
			std::cout << i << "\n";
			flag = false;
		}
		if (((clock() - t1) / CLOCKS_PER_SEC) == 15) {
			std::cout << i << "\n";
			break;
		}
	}

	system("pause");
	return 0;
}