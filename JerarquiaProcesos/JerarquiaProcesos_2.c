#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    pid_t pid;
    int i, n = 5;

    for(i = 1; i < n; i++)
    {
        pid = fork();

        sleep(3);
        printf("Soy %d \n",getpid());
        printf("y mi padre %d\n",getppid());
        if(pid == 0)
        {
            break;
        }
    }
    return 0;
}
