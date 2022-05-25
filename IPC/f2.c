#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

void Openwriting(int, float, int);
void Openreading(int, char *p, int);

int main(){
    //FIFO
    int fd;
    // create pipe
    if (mkfifo("myfifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo file.\n");
            return 1;
        }
    }
    //Space for recive 
    int kbNum = 1;
    int space = 59999;  
    int bytes = kbNum*space;
    char *data = malloc(bytes);
  
    Openreading(fd,data, bytes); //Reading , Llega hasta 59999
    //for (int i=0; i<bytes; i++){
    //    printf("Dato-> %c  \n", data[i]);
    //}  

    if (data == NULL){
        printf("No esta pasand nada");
    }
    else{
        //filling verification
        for (int i=0; i<bytes; i++){
            if(data[i] != 'a'){
                printf("It is not complete");
            }
        }
        //That's correct
        printf("Datos enviados:  \n" );
    }
}





void Openwriting(int fd, float avg_travel_time, int size ){
    fd = open("myfifo", O_WRONLY); // open pipe for writing
    if (fd == -1){
        printf("Error al abrir la tuberia");// can't open pipe
    }
    if (write(fd, &avg_travel_time, size) == -1){ // writing datas of send
        printf("Error al escribir"); // can't write from pipe
    }
    close(fd);
}
 
void Openreading(int fd, char *arrArrival, int size ){
    fd = open("myfifo", O_RDONLY); // open pipe for reading
    if (fd == -1){
        printf("Error al abrir la tuberia"); // can't open pipe
    }
    if (read(fd, arrArrival, size) == -1){ 
        printf("Error al leer"); // can't read from pipe
    } 

    close(fd); //close pipe
}