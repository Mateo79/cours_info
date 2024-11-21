#include <signal.h>

void (*f)(int a)
{
    printf("Interruption %d", a);
}

int main()
{
    
    signal(3, f);

    while (1)
    {
        sleep(1);
    }
    
    return 0;
}



