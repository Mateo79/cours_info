// communication unidirectionnelle processus père / fils

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define N 5

int main(void)
{
    int p1[2];
    int p2[2];

    pid_t retour;
  
    if (pipe(p1) == -1) handle_error("pipe");
    if (pipe(p2) == -1) handle_error("pipe");
    
    if ((retour = fork()) == -1) handle_error("fork");
    if (retour == 0 ) // Générateur
    {
        int val;

        close(p1[0]);
        close(p2[0]);
        close(p2[1]);

        srand(time(NULL));

        while (1)
        {
            val = (int) ((float) N * rand() / (RAND_MAX + 1.0)) - (N / 2);
            fprintf(stderr, "Gen[%i]> %i\n", getpid(), val);
            write(p1[1], &val, sizeof(val));
            sleep(1);
        }
    }
    else // père
{
        if ((retour = fork()) == -1) handle_error("fork");
        if (retour == 0 ) // Additionneur
        {
            close(p1[1]);
            close(p2[0]);

            int somme = 0;
            while (1)
            {
                int val;
                read(p1[0], &val, sizeof(val));
                somme += val;                
                fprintf(stderr, "Add[%i]> %i\n", getpid(), somme);
                write(p2[1], &somme, sizeof(somme));
            }
        
        }
        else // Afficheur
        {
            close(p1[0]);
            close(p1[1]);
            close(p2[1]);
            
            while (1)
            {
                int somme;
                read(p2[0], &somme, sizeof(somme));
                fprintf(stderr, "Aff[%i]> %i\n", getpid(), somme);
                printf("Resultat %i\n", somme);
            }
        }
    }
    return 0;
}
