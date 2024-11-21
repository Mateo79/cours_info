/* Fichier service.c */
#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>


#define NOM_DEMON "essaidemon"

int fd;
char * filename;

void signal_handler(int sig) 
{
    switch(sig) 
    {
        case SIGHUP:
            /* recharger la config */
            /* TODO */
            syslog(LOG_INFO, "recharger le service");
            break;

        case SIGTERM:
            /* TODO */
            lockf(fd, F_ULOCK, 0);
            close(fd);
            unlink(filename);
            syslog(LOG_INFO, "arrêt du service");
            closelog();
            exit(0);
            break;

        default:
            /* TODO */
            syslog(LOG_INFO, "signal (%d) %s\n", sig, strsignal(sig));
            break;
    }
}


void demon(char *fTmpLock)
{
    pid_t   pid;
    int       i;
    //int      fd;
    char str[2];
    filename = fTmpLock;

    /* processus fils orphelin rattacher à init */
    pid = fork();
    /* erreur */
    if (pid < 0) perror("Erreur fork().");
    /* processus père */
    if (pid > 0) exit(EXIT_SUCCESS);

    /* indépendance du processus */
    setsid();

    /* éviter processus zombie */
    pid = fork();
    /* erreur */
    if (pid < 0) perror("Erreur fork().");
    /* processus père */
    if (pid > 0) exit(EXIT_SUCCESS);

    /* vide et réinitialise les descripteurs de fichiers */
    for (i = getdtablesize(); i >=0; --i) close(i);
    i = open("/dev/null", O_RDWR);
    dup(i);
    dup(i);

    /* masque pour création de fichier */
    umask(022);

    /* détournement des signaux */
    signal(SIGHUP,  signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT,  signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGTSTP, signal_handler);


    /* ouverture syslog */
    openlog(NOM_DEMON, LOG_PID, LOG_DAEMON);

    /* se positionne dans /tmp */
    chdir("/tmp");

    /* une seule exécution par verrouillage sur fichier */
    fd = open(fTmpLock, O_RDWR | O_CREAT, 0640);
    if (fd < 0) 
    {
        syslog(LOG_ERR, "impossible d'ouvrir le fichier verrou: %s", fTmpLock);
        exit(EXIT_FAILURE);
    }
    if (lockf(fd, F_TLOCK, 0) < 0)
    {   
        syslog(LOG_WARNING, "le service est déja lancé");
        exit(EXIT_SUCCESS);
    }
    snprintf(str, 12, "%d\n", getpid());
    write(fd, str, strlen(str));

    /* informer du démarrage */
    syslog(LOG_INFO, "démarrage du service");
}

int main()
{
    demon("demon.lock");
    
    while(1) {
        sleep(1);
    } 
       
    return EXIT_SUCCESS;
}

