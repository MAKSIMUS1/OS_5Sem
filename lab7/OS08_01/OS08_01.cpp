#include <Windows.h>
#include <iostream>
#include <ctime>

int main()
{
	time_t t1;
	t1 = time(&t1);
	std::cout << " - 01.01.1979 Unix epoch: " << t1 << " sec\n";
	std::cout << " - in years about		  : " << t1 / (60 * 60 * 24 * 365) << " years\n";
	{
		char buf[50];
		errno_t error = ctime_s(buf, sizeof(buf), &t1); // Date in string
		std::cout << " -- ctime_s 		  : " << buf << "\n";
	}
	{
		tm ttm;
		gmtime_s(&ttm, &t1); // UTC время
		std::cout << " - gmtime_s -- \n";
		std::cout << " ---- tm.year			: " << ttm.tm_year << "\n";
		std::cout << " ---- tm.mon			: " << ttm.tm_mon << "\n";
		std::cout << " ---- tm.mday			: " << ttm.tm_mday << "\n";
		std::cout << " ---- tm.hour			: " << ttm.tm_hour << "\n";
		std::cout << " ---- tm.min			: " << ttm.tm_min << "\n";
		std::cout << " ---- tm.sec			: " << ttm.tm_sec << "\n";
		std::cout << " ---- tm.wday			: " << ttm.tm_wday << "\n";
		std::cout << " ---- tm.yday			: " << ttm.tm_yday << "\n";
		std::cout << " ---- tm.isdst		: " << ttm.tm_isdst << "\n";
	}
	{
		tm ttm;
		localtime_s(&ttm, &t1); // UTC время
		std::cout << " - gmtime_s -- \n";
		std::cout << " ---- tm.year			: " << ttm.tm_year << "\n";
		std::cout << " ---- tm.mon			: " << ttm.tm_mon << "\n";
		std::cout << " ---- tm.mday			: " << ttm.tm_mday << "\n";
		std::cout << " ---- tm.hour			: " << ttm.tm_hour << "\n";
		std::cout << " ---- tm.min			: " << ttm.tm_min << "\n";
		std::cout << " ---- tm.sec			: " << ttm.tm_sec << "\n";
		std::cout << " ---- tm.wday			: " << ttm.tm_wday << "\n";
		std::cout << " ---- tm.yday			: " << ttm.tm_yday << "\n";
		std::cout << " ---- tm.isdst		: " << ttm.tm_isdst << "\n";
	}
	{
		clock_t t1 = clock();
		std::cout << " - clock -- \n";
		std::cout << " ---- t1				: " << t1 << "\n";
		Sleep(2000);
		std::cout << " ---- Sleep(2000)\n";
		clock_t t2 = clock();
		std::cout << " ---- t2				: " << t2 << "\n";
		std::cout << " ---- t2-t1			: " << t2 - t1 << " = " << (t2 - t1) / CLOCKS_PER_SEC << " sec\n";
	}

	system("pause");
	return 0;
}