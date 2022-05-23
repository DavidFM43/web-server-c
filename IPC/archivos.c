/**
 * @file Vel_archivos.c
 * @author Juan Jose Figueroa - Eduardz Alexis Mendez - David Felipe Mora (jufigueroap@unal.edu.co - emendezc@unal.edu.co - dmorara@unal.edu.co)
 * @date 2022-05-18
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
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork.\n");
        exit(-1);
    }
    for (int j = 3; j < 9; j++)
    {
        if (pid == 0)
        {                                          // Proceso Hijo
            FILE *fl = fopen("Archivo.bin", "wb"); // Crear-Abrir binario para escritura
            if (fl == NULL)
            {
                perror("Error en escritura de archivo.\n");
                exit(-1);
            }
            char c = 'a';
            int l = pow(10, j);
            char *ap = malloc(sizeof(char) * l);
            if (ap == NULL)
            {
                perror("Error en apuntador (hijo).\n");
                exit(-1);
            }
            for (int i = 0; i < l; i++)
            {
                ap[i] = c;
            }
            start = clock();                 // Tiempo inicial
            fwrite(ap, sizeof(char), l, fl); // Escritura en binario
            end = clock();                   // Tiempo Final
            fclose(fl);                      // Cerrar binairo
            free(ap);
            time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Tiempo total
            son[j - 3] = time_used;
            printf("%s\n", "Se escribio en el archivo binario.");
        }
        else
        { // Proceso Padre

            FILE *fl = fopen("Archivo.bin", "rb"); // Abrir binario para lectura
            if (fl == NULL)
            {
                perror("Error en lectura de archivo.\n");
                exit(-1);
            }
            int l = pow(10, j);
            char *ap = malloc(sizeof(char) * l);
            wait(NULL);
            start = clock();                                      // Tiempo Inicial
            fread(ap, sizeof(char), l, fl);                       // Lectura del binario
            end = clock();                                        // Tiempo Final
            fclose(fl);                                           // Cerrar el binario
            time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Tiempo total
            father[j - 3] = time_used;
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
