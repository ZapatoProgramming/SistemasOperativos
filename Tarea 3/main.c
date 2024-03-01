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
void writeArrayTotxtFromConsole(int fd){
    int tempArray[5];
    printf("\n");
    for(int i = 0; i < 5;i++) {
        printf("Escriba el valor %d del arreglo: ",i+1);
        scanf("%d",&tempArray[i]);
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
    int fd;
    creat("datos.txt",111111111);
    creat("datos2.txt",111111111);
    printf("Del archivo data.txt-----------------------------------------------------------\n");
    fd = open("datos123123123.txt",1);//hacemos el descriptor de solo escritura para el archivo 1
    isValid(fd); //revisa si es valido el descriptor
    fillArray(fd);
    close(fd);
    fd = open("datos.txt",0);//hacemos el descriptor de solo lectura para el archivo 1
    isValid(fd);
    printArrayFromFile(fd);
    close(fd);
    printf("\nDel archivo data2.txt------------------------------------------------------------");
    fd = open("datos2.txt",1);//hacemos el descriptor de solo escritura para el archivo 2
    isValid(fd);
    writeArrayTotxtFromConsole(fd);
    close(fd);
    fd = open("datos2.txt",0);//hacemos el descriptor de solo lectura para el archivo 2
    isValid(fd);
    printArrayFromFile(fd);
    close(fd);
    printf("\n");
    return 0;
}
