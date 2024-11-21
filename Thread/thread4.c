#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void   *my_thread_process(void *arg)
{
    int     i;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    for (i = 0; i < 5; i++)
    {
        printf("Thread %s: %d\n", (char *)arg, i);
        sleep(1);
        pthread_testcancel();
    }

    return NULL;
}

int main()
{
    pthread_t th1;
    void   *ret;

    if (pthread_create(&th1, NULL, my_thread_process, "1") < 0)
    {
        fprintf(stderr, "pthread_create error for thread 1\n");
        exit(1);
    }

    sleep(2);
    if (pthread_cancel(th1) != 0)
    {
        fprintf(stderr, "pthread_cancel error for thread 1\n");
        exit(1);
    }

    pthread_join(th1, &ret);

    return 0;
}
