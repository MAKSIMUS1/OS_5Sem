#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void* OS04_07_T1(void * arg)
{
    pid_t pid = getpid();
    pid_t tid = pthread_self();
    int xtid = syscall(SYS_gettid);
    for(int i = 0; i < 75; i++)
    {
        sleep(1);
        printf("OS04_07_T1 thread %d-%d, tid = %d, xtid = %d \n", pid, i, tid, xtid);
    }
    pthread_exit("OS04_07_T1 thread");
}

int main()
{
    pthread_t a_thread;
    void* thread_result;
    pid_t pid = getpid();
    printf("main: pid = %d \n", pid);
    int res = pthread_create(&a_thread, NULL, OS04_07_T1, NULL);
    printf("tid = %d\n", a_thread);
    for(int i = 0; i < 10; i++)
    {
        sleep(1);
        printf("%d-%d \n", pid, i);
    }

    int status = pthread_join(a_thread, (void**)&thread_result);
    exit(0);
}