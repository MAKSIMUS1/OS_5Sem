#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int main()
{
    time_t t = 0;
    t = time(&t);
    printf("main: time = %d\n", t);
    struct tm *tmptr;
    tmptr = gmtime(&t);
    printf("%d.%d.%d %d:%d:%d\n", tmptr->tm_mday, tmptr->tm_mon+1, tmptr->tm_year, tmptr->tm_hour, tmptr->tm_min, tmptr->tm_sec);
    sleep(1);
    printf("main clock = %d\n", (int)clock());
    exit(0);
}