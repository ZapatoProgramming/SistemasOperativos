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

void fillArray(int fd){
    int tempArray[5] = {1,2,3,4,5};
    for(int i = 0; i < 10;i++) {
        write(fd,&tempArray[i],sizeof(tempArray[0]));
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

 pid_t pid;
 int x = 5, y = 10;

 pid = fork();

 // Código del hijo
        if( pid == 0)
        {
            printf("Soy el hijo de %d, mi trabajo es llenar el arreglo en datos.txt\n",getppid());
            int fd;
            fd = open("datos.txt",1);//hacemos el descriptor de solo escritura para el archivo 1
            isValid(fd); //revisa si es valido el descriptor
            fillArray(fd);
            close(fd);
        }

        // Código del padre
        if( pid > 0)
        {
            sleep(3); 
            printf("Soy el padre (%d) mi trabajo es leer el archivo e imprimirlo en consola\n",getpid());
            int fd;
            fd = open("datos.txt",0);//hacemos el descriptor de solo lectura para el archivo 0
            isValid(fd); //revisa si es valido el descriptor
            printArrayFromFile(fd);
            close(fd);
        }
        printf("\n");

    return 0;

}