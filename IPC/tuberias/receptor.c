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

void Openwriting(float, int);
void Openreading(char *p, int);

int main(int argc, char *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Incorrect number of arguments supplied.\n");
        exit(-1);
    }
    int kbNum = atoi(argv[1]);

    // create pipe
    if (mkfifo("myfifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo file.\n");
            return 1;
        }
    }

    int bytes = kbNum * 1024;
    char *data = malloc(bytes);

    clock_t begin = clock();
    Openreading(data, bytes); // Reading
    clock_t end = clock();    // termina de contabilizar

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // tiempo de escritura

    printf("read time: %f segs.\n", time_spent);

    // here, measuere time

    if (data == NULL)
    {
        printf("File Null");
    }
    else
    {
        // filling verification
        for (int i = 0; i < bytes; i++)
        {
            if (data[i] != 'a')
            {
                // printf("Number end: %d \n", i ); //limit to 65536 in data[i]
                break;
            }
        }
        // printf("check \n");
    }
}

void Openwriting(float avg_travel_time, int size)
{
    int fd;
    fd = open("myfifo", O_WRONLY); // open pipe for writing
    if (fd == -1)
    {
        printf("Error al abrir la tuberia"); // can't open pipe
    }
    if (write(fd, &avg_travel_time, size) == -1)
    {                                // writing datas of send
        printf("Error al escribir"); // can't write from pipe
    }
    close(fd);
}

void Openreading(char *arrArrival, int size)
{
    int fd;
    fd = open("myfifo", O_RDONLY); // open pipe for reading
    if (fd == -1)
    {
        printf("Error al abrir la tuberia"); // can't open pipe
    }
    if (read(fd, arrArrival, size) == -1)
    {
        printf("Error al leer"); // can't read from pipe
    }

    close(fd); // close pipe
}