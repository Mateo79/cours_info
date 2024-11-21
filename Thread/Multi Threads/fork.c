#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int     i;

int main(int ac, char **av)
{
    int     pid;

    i = 1;

    if ((pid = fork()) == 0)
    {
        /* Dans le fils */
        printf("Je suis le fils, pid = %d\n", getpid());
        sleep(2);
        printf("Fin du fils, i = %d !\n", i);
        exit(0);
    }
    else if (pid > 0)
    {
        /* Dans le pere */
        printf("Je suis le pere, pid = %d\n", getpid());
        sleep(1);

        /* Modifie la variable */
        i = 2;
        printf("le pere a modifie la variable a %d\n", i);

        sleep(3);
        printf("Fin du pere, i = %d !\n", i);
        exit(0);
    }
    else
    {
        /* Erreur */
        perror("fork");
        exit(1);
    }
    return 0;
}
