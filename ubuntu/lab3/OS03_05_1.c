#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    for(int i = 0; i < 50; i++)
    {
        printf("%d.OS03_05_1 -- Process ID: %d\n", i + 1,  getpid());
        sleep(1);
    }
}