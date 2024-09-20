#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int rv;
    switch(pid=fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            printf(" CHILD: Это процесс-потомок!\n");
            printf(" CHILD: Мой PID -- %d\n", getpid());
            printf(" CHILD: PID моего родителя -- %d\n", getppid());
            sleep(4);
            for(int i = 0; i < 50; i++)
            {
                printf("%d.Process ID: %d\n", i + 1,  getpid());
                sleep(1);
            }
            printf(" CHILD : Выход!\n");
            exit(rv);
        default: 
            printf(" PARENT: Это процесс-родитель!\n");
            printf(" PARENT: Мой PID -- %d\n", getpid());
            printf(" PARENT: PID моего потомка -- %d\n", pid);
            printf(" PARENT: Я жду, пока потомок не вызовет exit()...\n");
            printf(" PARENT: Код возрата потомка:%d\n", WEXITSTATUS(rv));

            for(int i = 0; i < 100; i++)
            {
                printf("%d.Process ID: %d\n", i + 1,  getpid());
                sleep(1);
            }
            printf(" PARENT: Выход!\n");
    }
    return 0;
}