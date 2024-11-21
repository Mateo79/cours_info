// execution de la commande ls -l | wc -l

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main()
{
    int p[2];
    pid_t retour;
    
    if (pipe(p) == -1) handle_error("pipe");
    
    if ((retour = fork()) == -1) handle_error("fork");

    if (retour == 0 ) // fils
    {
        close(STDOUT_FILENO);
        dup(p[1]);
        close(p[1]);
        close(p[0]);
        execlp("ls", "ls", "-l", NULL);
    }
    else // père
    {
        close(STDIN_FILENO);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        execlp("wc", "wc", "-l", NULL);
    }
    return 0;
}
