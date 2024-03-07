#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void isValid(int fd){
    if( fd < 0 )
    {
        if( errno == EAGAIN )
        {
            printf("Archivo bloqueado.\n");
            exit(1);
        }
        else if( errno == EACCES )
        {
            printf("Hubo un error en los permisos del archivo.\n");
            exit(1);
        }
        else if( errno == EBADF )
        {
            printf("Mal descriptor del archivo.\n");
            exit(1);
        }
        else
        {
            printf("No se conoce el error.\n");
            exit(1);
        }
    }
}

void fillEvenArray(int fd){
    int tempArray[10] = {2,4,6,8,10,12,14,16,18,20};
    for(int i = 0; i < 10;i++) {
        write(fd,&tempArray[i],sizeof(tempArray[0]));
    }
}

void fillOddArray(int fd){
    int tempArray[10] = {1,3,5,7,9,11,13,15,17,19};
    for(int i = 0; i < 10;i++) {
        write(fd,&tempArray[i],sizeof(tempArray[0]));
    }
}
void sumArrays(int fd1, int fd2){
    int tempArray[10];
    int tempArray2[10];
    int resultArray[10];
    printf("Suma de los arreglos de los txt: \n");
    for(int i = 0; i < 10;i++) {
        read(fd1,&tempArray[i],sizeof(tempArray[0]));
        read(fd2,&tempArray2[i],sizeof(tempArray[0]));
        resultArray[i] = tempArray[i] + tempArray2[i];
        printf("%d + %d = %d\n",tempArray[i],tempArray2[i],resultArray[i]);

    }
}

void printArrayFromFile(int fd){
    int tempArray[5];
    printf("Arreglo escrito en el txt: ");
    for(int i = 0; i < 5;i++) {
        read(fd,&tempArray[i],sizeof(tempArray[0]));
        if(i < 4)
        {
            printf(" %d,",tempArray[i]);
        } else
        {
            printf(" %d ",tempArray[i]);
        }
    }
}

int main() {
    creat("N.txt",111111111);
    creat("M.txt",111111111);
    pid_t pid_n,pid_m,pid_R;
    pid_R = fork();
    if(pid_R == 0)
    {
        pid_n = fork();
        // Código del hijo N
        if( pid_n == 0)
        {
            printf("Soy N (%d), el hijo de R (%d), mi trabajo es llenar el arreglo de pares en N.txt\n",getpid(),getppid());
            int fd;
            fd = open("N.txt",1);//hacemos el descriptor de solo escritura para el archivo 1
            isValid(fd); //revisa si es valido el descriptor
            fillEvenArray(fd);
            close(fd);
            exit(0);

        }
        pid_m = fork();
        // Código del hijo M
        if( pid_m == 0)
        {
            printf("Soy M (%d), el hijo de R (%d), mi trabajo es llenar el arreglo de impares en M.txt\n",getpid(),getppid());
            int fd;
            fd = open("M.txt",1);//hacemos el descriptor de solo escritura para el archivo 1
            isValid(fd); //revisa si es valido el descriptor
            fillOddArray(fd);
            close(fd);
            exit(0);

        }
        sleep(1);
        printf("Soy R (%d), padre de N y M, mi trabajo es leer los archivos N.txt y M.txt, sumar cada valor 1 por 1 e imprimir los resultados en consola\n",getpid());
        int fd;
        int fd2;
        fd = open("N.txt",0);//hacemos el descriptor de solo lectura para el archivo 0
        fd2 = open("M.txt",0);//hacemos el descriptor de solo lectura para el archivo 0
        isValid(fd); //revisa si es valido el descriptor
        isValid(fd2); //revisa si es valido el descriptor
        sumArrays(fd,fd2);
        close(fd);
        close(fd2);
        printf("\n");
        exit(0);
    }

    sleep(3);
    return 0;

}
