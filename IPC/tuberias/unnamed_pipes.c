/**
 * @file unnamed_pipes.c
 * @author Juan Jose Figueroa - Eduardz Alexis Mendez - David Felipe Mora (jufigueroap@unal.edu.co - emendezc@unal.edu.co - dmorara@unal.edu.co)
 * @date 2022-05-24
 *
 *
 * @see Incluir libreria math en el compilador
 *
 * @warning Para este programa solo se tiene en cuenta hasta 10^5kb dado que las tuberias tienen
 * un size predeterminado el cual al superarse hace que la funcion write se vuelva bloqueante
 * y no permita llevar a cabo el ejercicio de forma correcta. Incluso el programa a veces
 * tiene problemas en 10^4kb.
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
    double father[3];
    double son[3];
    int fd[3][2];
    for (int j = 0; j < 2; j++)
    {
        if (pipe(fd[j]) == -1)
        {
            printf("Error en crear %d tuberia.\n", j);
            exit(-1);
        }
    }
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork.\n");
        exit(-1);
    }
    for (int j = 3; j < 6; j++)
    {
        if (pid == 0)
        { // Proceso Hijo
            close(fd[j - 3][0]);
            char c = 'a';
            int l = pow(10, j);
            char *ap = malloc(sizeof(char) * l);
            if (ap == NULL)
            {
                perror("Error al encolar.\n");
                exit(-1);
            }
            for (int i = 0; i < l; i++)
                *(ap + i) = c;
            start = clock();
            write(fd[j - 3][1], ap, l);
            end = clock();
            close(fd[j - 3][1]);
            time_used = ((double)end - start) / CLOCKS_PER_SEC;
            son[j - 3] = time_used;
            free(ap);
            printf("%s\n", "Se escribio en el archivo binario.");
        }
        else
        { // Proceso Padre

            close(fd[j - 3][1]);
            int l = pow(10, j);
            char *ap = malloc(sizeof(char) * l);
            if (ap == NULL)
            {
                perror("Error al desencolar.\n");
                exit(-1);
            }
            wait(NULL);
            start = clock();
            read(fd[j - 3][0], ap, l);
            end = clock();
            close(fd[j - 3][0]);
            time_used = ((double)end - start) / CLOCKS_PER_SEC;
            father[j - 3] = time_used;
            free(ap);
            printf("%s\n", "Se leyo del archivo binario.");
        }
    }
    if (pid == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Tiempo del hijo en 10^ %d kb: %f  \n", i + 3, son[i]);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Tiempo del padre en 10^ %d kb: %f \n", i + 3, father[i]);
        }
    }
    return 0;
}
