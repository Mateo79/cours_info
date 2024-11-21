
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void   *thread_process(void *arg)
{
    int     i;

    for (i = 0; i < 5; i++)
    {
        printf("Thread %s: %d\n", (char *)arg, i);
        sleep(1);
    }

    pthread_exit(0);
}

int main()
{
    pthread_t th1, th2;
    void   *ret;

    if (pthread_create(&th1, NULL, thread_process, "1") < 0)
    {
        fprintf(stderr, "pthread_create error for thread 1\n");
        exit(1);
    }

    if (pthread_create(&th2, NULL, thread_process, "2") < 0)
    {
        fprintf(stderr, "pthread_create error for thread 2\n");
        exit(1);
    }

    pthread_join(th1, &ret);
    pthread_join(th2, &ret);

    return 0;
}






