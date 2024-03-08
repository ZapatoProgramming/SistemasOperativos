//make a program that makes  a for loop that prints a random number 4 times
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

int main()
{
    int aleatorio;
    srand(time(NULL));
    for(int i = 0; i < 4; i++)
    {
        aleatorio = rand() % 100;
        printf("Soy el proceso %d y mi numero es %d\n", getpid(), aleatorio);
    }
    return 0;
}
