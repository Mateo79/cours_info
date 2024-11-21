#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t   pid, pidFils, pidCourant;

	pid = fork();
	pidCourant = getpid();

	if (pid > 0) { /* Processus père */
		printf("processus père, pid: %i\n", pidCourant);
		pidFils = wait(NULL);
	} else if (pid == 0) { /* Processus fils */
		printf("processus fils, pid: %i\n", pidCourant);
		while (1); /* boucle infinie */
	}
}
