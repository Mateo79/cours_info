// communication unidirectionnelle processus père / fils

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
    int p[2];
    int status;
    pid_t retour;
    char message[32];
    
    if (pipe(p) == -1) handle_error("pipe");
    
    if ((retour = fork()) == -1) handle_error("fork");

    if (retour == 0 ) // fils
    {
        close(p[0]);
        strcpy(message, "bonjour");
        write(p[1], message, strlen(message) + 1);
        printf("fils[%i]> message envoyé: %s\n", getpid(), message);
        close(p[1]);
        sleep(60);
        exit(0);
    }
    else // père
    {
        close(p[1]);
        read(p[0], message, 32);
        printf("père[%i]> message reçu: %s\n", getpid(), message);
        close(p[0]);
        sleep(60);
        wait(&status);
    }
    return 0;
}
