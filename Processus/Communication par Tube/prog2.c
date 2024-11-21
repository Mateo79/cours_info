// communication bidirectionnelle processus père / fils

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main()
{
    int p1[2];
    int p2[2];
    int status;
    pid_t retour;
    char message[32];
    
    if (pipe(p1) == -1) handle_error("pipe");
    if (pipe(p2) == -1) handle_error("pipe");
    
    if ((retour = fork()) == -1) handle_error("fork");

    if (retour == 0 ) // fils
    {
        close(p1[1]);
        close(p2[0]);
        read(p1[0], message, 32);
        printf("fils[%i]> message reçu: %s\n", getpid(), message);
        strcpy(message, "réponse!");
        write(p2[1], message, strlen(message) + 1);
        close(p1[0]);
        close(p2[1]);
        exit(0);
    }
    else // père
    {
        close(p1[0]);
        close(p2[1]);
        strcpy(message, "question?");
        read(p2[0], message, 32);
        write(p1[1], message, strlen(message) + 1);
        //read(p2[0], message, 32);
        printf("père[%i]> message reçu: %s\n", getpid(), message);
        close(p1[1]);
        close(p2[0]);
        wait(&status);
    }
    return 0;
}
