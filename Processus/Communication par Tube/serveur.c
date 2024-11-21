#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define FIFO1 "/tmp/fichierFifo1"
#define FIFO2 "/tmp/fichierFifo2"

int main()
{
    int fifo1;
    int fifo2;
    char message[32];
    int nb1;
    int nb2;
    
    if(mkfifo(FIFO1, S_IRUSR | S_IWUSR) == -1) handle_error("mkfifo");
    if(mkfifo(FIFO2, S_IRUSR | S_IWUSR) == -1) handle_error("mkfifo");

    if((fifo1 = open(FIFO1, O_RDONLY)) == -1) handle_error("open");
    if((fifo2 = open(FIFO2, O_WRONLY)) == -1) handle_error("open");
    
   
    read(fifo1, message, 32);
    nb1 = atoi(message);
    read(fifo1, message, 32);
    nb2 = atoi(message);
    sprintf(message, "%d", nb1 + nb2);
    write(fifo2, message, strlen(message) + 1);
    
    close(fifo1);
    close(fifo2);

    return 0;
}
