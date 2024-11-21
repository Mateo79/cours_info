// execution de la commande ls -l | wc -l

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define FIFO "/tmp/fichierFifo"

int main()
{
    int fifo;
    char message[32];
    
    if(mkfifo(FIFO, S_IRUSR | S_IWUSR) == -1) handle_error("mkfifo");

    if((fifo = open(FIFO, O_WRONLY)) == -1) handle_error("open");
    
    strcpy(message, "envoi d'un message");
    write(fifo, message, strlen(message) + 1);
    
    close(fifo);

    return 0;
}
