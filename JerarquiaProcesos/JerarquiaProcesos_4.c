#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    pid_t pid_R, pid_T,pid_W,pid_V, pid_S, pid_L, pid_P;

    pid_R = fork();
    if(pid_R == 0)
    {
        printf("soy R (%d) hijo de linux\n",getpid());
        pid_T = fork();
        if(pid_T == 0){
            printf("soy T (%d) y mi padre es R (%d)\n",getpid(),getppid());
            pid_V = fork();
            if(pid_V == 0){
                printf("soy V (%d) y mi padre es T (%d)\n",getpid(),getppid());
                exit(0);
            }
            exit(0);
        }
        pid_W = fork();
        if(pid_W == 0){
            printf("soy W (%d) y mi padre es R (%d)\n",getpid(),getppid());
            pid_S = fork();
            if(pid_S == 0){
                printf("soy S (%d) y mi padre es W (%d)\n",getpid(),getppid());
                exit(0);
            }
            pid_L = fork();
            if(pid_L == 0){
                printf("soy L (%d) y mi padre es W (%d)\n",getpid(),getppid());
                pid_P = fork();
                if(pid_P == 0){
                    printf("soy P (%d) y mi padre es L (%d)\n",getpid(),getppid());
                    exit(0);
                }
                exit(0);
            }
            exit(0);
        }

        exit(0);
    }
    sleep(3);
    return 0;
}
