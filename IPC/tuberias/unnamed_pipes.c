/**
 * @file name_pipe.c
 * @author Juan Jose Figueroa - Eduardz Alexis Mendez - David Felipe Mora (jufigueroap@unal.edu.co - emendezc@unal.edu.co - dmorara@unal.edu.co)
 * @date 2022-05-24
 *
 *
 * @see Include math librarie in the compiler
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    clock_t start, end; // Variables tiempo
    double time_used;   // Tiempo final
    double father[6];
    double son[6];
    int fd[2];
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork.\n");
        exit(-1);
    }
    if(pipe(fd) == -1){
        perror("Error en crear la pipe.\n");
        exit(-1);
    }
    for (int j = 3; j < 9; j++)
    {
        if (pid == 0)
        {                                          // Proceso Hijo
            close(fd[0]);
            char c = 'a';
            int l = pow(10,j);
            char *ap = malloc(sizeof(char)*l);
            if(ap == NULL){
                perror("Error al encolar.\n");
                exit(-1);
            }
            for(int i = 0; i < l; i++)
                *(ap+i) = c;
            start = clock();
            write(fd[1], ap, l);
            end = clock();
            time_used = ((double)end-start)/CLOCKS_PER_SEC;
            son[j-3] = time_used;
            printf("%s\n", "Se escribio en el archivo binario.");
        }
        else
        { // Proceso Padre

            close(fd[1]);
            int l = pow(10,j);
            char *ap = malloc(sizeof(char)*l);
            if(ap == NULL){
                perror("Error al desencolar.\n");
                exit(-1);
            }
            wait(NULL);
            start = clock();
            read(fd[0], ap, l);
            end = clock();
            time_used = ((double)end-start)/CLOCKS_PER_SEC;
            father[j-3] = time_used;
            printf("%s\n", "Se leyo del archivo binario.");
        }
    }
    if (pid == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            printf("Tiempo del hijo en 10^%dkb: %fs \n", i + 3, son[i]);
        }
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            printf("Tiempo del padre en 10^%dkb: %fs \n", i + 3, father[i]);
        }
    }
    return 0;
}
