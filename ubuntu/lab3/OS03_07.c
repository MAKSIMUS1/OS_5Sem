#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"./OS03_05_1", NULL};
    execv(args[0], args);
    for(int i = 0; i < 100; i++)
    {
        printf("Process ID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}