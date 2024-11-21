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
    
    if((fifo = open(FIFO, O_RDONLY)) == -1) handle_error("open");
    
    read(fifo, message, 32);
    printf("Message lu: %s\n", message);
    
    close(fifo);

    return 0;
}
