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
#include <time.h>

int main()
{
    clock_t start, end; //Variables tiempo
    double time_used; //Tiempo final
    double father[6];
    double son[6];
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork.\n");
        exit(-1);
    }
    if (pid == 0)
    { // Proceso Hijo
        for (int j = 3; j < 9; j++)
        {
            FILE *fl = fopen("Archivo.bin", "wb"); //Crear/Abrir binario para escritura
            if (fl == NULL)
            {
                perror("Error en escritura de archivo.\n");
                exit(-1);
            }
            start = clock(); // Tiempo inicial
            char c = 'a';
            int cti = c;
            int l = 8*pow(10, j);
            for (int i = 0; i < l; i++)
            {
                fwrite(&cti, sizeof(int), 1, fl); //Escritura en binario
            }
            //printf("%s\n", "Se escribio en el archivo binario.");
            fclose(fl); // Cerrar binairo
            end = clock(); // Tiempo Final
            time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Tiempo total
            son[j-3] = time_used;
        }
        printf("%s\n", "Se escribio en el archivo binario.");
        for(int i = 0; i < 6; i++){
            printf("Tiempo del hijo en 10^%dkb: %fs \n", i+3, son[i]);
        }
    }
    else
    { // Proceso Padre
        for (int j = 3; j < 9; j++)
        {
            FILE *fl = fopen("Archivo.bin", "rb"); //Abrir binario para lectura
            if (fl == NULL)
            {
                perror("Error en lectura de archivo.\n");
                exit(-1);
            }
            start = clock(); // Tiempo Inicial
            int b;
            int l = 8*pow(10, j);
            for (int i = 0; i < l; i++)
            {
                fread(&b, sizeof(int), 1, fl); // Lectura del binario
            }
            //printf("\nSe leyo del binario.\n");
            fclose(fl); // Cerrar el binario
            end = clock(); // Tiempo final
            time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Tiempo total
            father[j-3] = time_used;
        }
        printf("%s\n", "Se leyo del archivo binario.");
        for(int i = 0; i < 6; i++){
            printf("Tiempo del padre en 10^%dkb: %fs \n", i+3, father[i]);
        }
    }
    return 0;
}
