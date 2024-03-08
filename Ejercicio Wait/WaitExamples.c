#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define n 3

int main()
{
    int status, aleatorio, processes = 0;
    pid_t  pid_A, pid_B, pid_M;

    pid_A = fork();
    if(pid_A == 0)
    {
        srand(getpid());
        aleatorio = rand() % 100;
        printf("Soy A (%d) mi numero es %d\n", getpid(), aleatorio);
        return(0);
    }
    pid_B = fork();
    if(pid_B == 0)
    {
        srand(getpid());
        aleatorio = rand() % 100;
        printf("Soy B (%d) mi numero es %d\n", getpid(), aleatorio);
        
        return(0);
    }
    pid_M = fork();
    if(pid_M == 0)
    {
        srand(getpid());
        aleatorio = rand() % 100;
        printf("Soy M (%d) mi numero es %d\n", getpid(), aleatorio);
        return(0);
    }
    
    if( pid_A > 0 && pid_B > 0 && pid_M > 0)
    {
        for(int i = 0; i < n; i++)
        {
            wait(&status);
            if(WEXITSTATUS(status) == 0)
            {
                processes++;
            }
        }
        if(processes == 3)
        {
            printf("Todos los procesos finalizaron correctamente");
        }
    }

    printf("\n");
    return 0;
}