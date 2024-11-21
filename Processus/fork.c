#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// compilation:  gcc -o fork fork.c -Wall -O2

int main()
{
    pid_t   pid, pidCourant;

    pid = fork();
    pidCourant = getpid();

    if (pid > 0)                /* Processus père */
    {
        printf("processus père, pid: %i\n", pidCourant);
        while (1)               /* boucle */
        {
            putchar('p');
            fflush(stdout);
            sleep(2);
        }
    }
    else if (pid == 0)          /* Processus fils */
    {
        printf("processus fils, pid: %i\n", pidCourant);
        while (1)               /* boucle */
        {
            putchar('f');
            fflush(stdout);
            sleep(2);
        }

    }

    return 0;
}
