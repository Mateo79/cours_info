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
    
    if((fifo1 = open(FIFO1, O_WRONLY)) == -1) handle_error("open");
    if((fifo2 = open(FIFO2, O_RDONLY)) == -1) handle_error("open");
    
    printf("donner 2 nombres à additionner: ");
    scanf("%d", &nb1);
    scanf("%d", &nb2);
    
    sprintf(message, "%d", nb1);
    write(fifo1, message, strlen(message) + 1);
    sprintf(message, "%d", nb2);
    write(fifo1, message, strlen(message) + 1);
   
    read(fifo2, message, 32);
    printf("Le résultat est: %s\n", message);
    
    close(fifo1);
    close(fifo2);
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
