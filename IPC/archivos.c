#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

int main()
{
    clock_t start, end;
    double time_used;
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork.\n");
        exit(-1);
    }
    if (pid == 0)
    {
        for (int j = 3; j < 9; j++)
        {
            FILE *fl = fopen("Archivos.bin", "wb");
            start = clock();
            if (fl == NULL)
            {
                perror("Error en file pointer.\n");
                exit(-1);
            }
            char c = 'a';
            int cti = c;
            int l = pow(10, j);
            for (int i = 0; i < l; i++)
            {
                fwrite(&cti, sizeof(int), 1, fl);
            }
            printf("Se escribio en el archivo binario.\n");
            fclose(fl);
            end = clock();
            time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Tiempo de escritura (hijo) de 10^%d bytes: %fs. \n", j, time_used);
        }
    }
    else
    {
        for (int j = 3; j < 9; j++)
        {
            FILE* fl = fopen("Archivos.bin", "rb");
            start = clock();
            if (fl == NULL)
            {
                perror("Error en file pointer.\n");
                exit(-1);
            }
            int b;
            int l = pow(10, j);
            for (int i = 0; i < l; i++)
            {
                fread(&b, sizeof(int), 1, fl);
            }
            fclose(fl);
            end = clock();
            time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Tiempo de lectura (Padre) de 10^%d bytes: %fs. \n", j, time_used);
        }
    }
    return 0;
}