#include <stdio.h>
#include <unistd.h>

int main()
{
    system("./OS03_05_1");
    for(int i = 0; i < 100; i++)
    {
        printf("Process ID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}