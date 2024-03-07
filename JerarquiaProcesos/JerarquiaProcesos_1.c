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

        if(pid != 0)
        {
            sleep(3);
            printf("Soy %d \n",getpid());
            printf("y mi padre %d\n",getppid());

            break;
        }
    }

    return 0;
}
