#include <stdio.h>
#include <signal.h>
#include <unistd.h>
 
#define NB_COMPTEURS 32

const char* signals[] = { 
    "", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP",
    "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1",
    "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM",
    "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP",
    "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ",
    "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR"};

int compteurs[NB_COMPTEURS];

void trait_sig_term(int sig)
{
    compteurs[sig]++;

    printf("Réception du signal: %d) %s, compteur: %d\n", 
        sig, signals[sig], compteurs[sig]);

    if (compteurs[sig] == 5)
    {
        printf("Rétablir la valeur par défaut pour %s\n", signals[sig]);
        signal(sig, SIG_DFL);
    }
}

int main()
{
    int i;
    // initialisation des compteurs 
    for (i = 0; i < NB_COMPTEURS; i++) compteurs[i] = 0;

    // quelques signaux détournés
    signal(SIGHUP,  trait_sig_term);
    signal(SIGINT,  trait_sig_term);
    signal(SIGQUIT, trait_sig_term);
    signal(SIGILL,  trait_sig_term);
    signal(SIGTRAP, trait_sig_term);
    signal(SIGABRT, trait_sig_term);
    signal(SIGBUS,  trait_sig_term);
    signal(SIGFPE,  trait_sig_term);
    signal(SIGTERM, trait_sig_term);

    signal(SIGUSR1,  trait_sig_term);
    signal(SIGSEGV,  trait_sig_term);
    signal(SIGUSR2,  trait_sig_term);
    signal(SIGPIPE,  trait_sig_term);
    signal(SIGALRM,  trait_sig_term);
    signal(SIGTERM,  trait_sig_term);
    signal(SIGSTKFLT,  trait_sig_term);
    signal(SIGCHLD,  trait_sig_term);
    signal(SIGCONT,  trait_sig_term);
    signal(SIGSTOP,  trait_sig_term);
    signal(SIGTSTP,  trait_sig_term);
    signal(SIGTTIN,  trait_sig_term);
    signal(SIGTTOU,  trait_sig_term);
    signal(SIGURG,   trait_sig_term);
    signal(SIGXCPU,  trait_sig_term);
    signal(SIGXFSZ,  trait_sig_term);
    signal(SIGVTALRM,  trait_sig_term);
    signal(SIGPROF,  trait_sig_term);
    signal(SIGWINCH, trait_sig_term);
    signal(SIGIO,    trait_sig_term);
    signal(SIGPWR,   trait_sig_term);

    while (1)
    {
        putchar('.');
        fflush(stdout);
        sleep(2);
    }
    
    return 0;
}

