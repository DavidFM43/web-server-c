#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ride.h"
#define TABLE_SIZE 1200

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main()
{

    // open files
    FILE *bfp = fopen("data/rides.bin", "rb");
    FILE *source_id_table_file = fopen("data/source_id_table.bin", "rb");
    if (bfp == NULL || source_id_table_file == NULL)
    {
        printf("Can't open files");
        exit(-1);
    }

    // initialize table
    int source_id_table[TABLE_SIZE];
    for (int i = 0; i < 1200; i++)
    {
        source_id_table[i] = -1;
    }
    // load source id table
    fread(&source_id_table, sizeof(source_id_table), 1, source_id_table_file);

    // seach parameters
    int source_id;
    int dest_id;
    int hour;
    int infile_pos;
    bool found;

    // Inicializando la FIFO, el arreglo de recibido y paquete de envio
    int arrArrival[3];
    int fd;
    float avg_travel_time;

    // create pipe
    if (mkfifo("myfifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
    }

    while (true)
    {
        printf("Abriendo archivo para lectura...\n");
        fd = open("myfifo", O_RDONLY); // Open pipe for reading
        if (fd == -1)
        {
            printf("Can't open pipe from reading.\n");
            return 1;
        }
        if (read(fd, &arrArrival, sizeof(arrArrival)) == -1)
        { // read attributes to arrArrival array
            printf("Can't read from pipe\n");
            return 2; // read error
        }

        // Almacenando los datos de envio
        source_id = arrArrival[0];
        dest_id = arrArrival[1];
        hour = arrArrival[2];
        Ride *ride = malloc(sizeof(Ride)); // reservar memoria
        printf("Aquí ya esta leido\n");
        close(fd); // Close pipe

        printf("Criterios: %d, %d, %d\n", source_id, dest_id, hour);

        // seach procedure
        if (source_id_table[source_id] == -1)
        {
            // No rides with that source id
            avg_travel_time = -1.0;
            printf("Abriendo archivo para escritura. \n");
            fd = open("myfifo", O_WRONLY);
            if (write(fd, &avg_travel_time, sizeof(float)) == -1)
            {
                printf("Can't write in pipe.");
                return 2;
            }
            close(fd); // Cerramos el archivo de envio
            break;
        }
        else
        {
            infile_pos = source_id_table[source_id];
            found = false;
            do // search through the linked list of the source ID
            {
                fseek(bfp, infile_pos, SEEK_SET);
                fread(ride, sizeof(Ride), 1, bfp);
                if (ride->hour == hour && ride->dest_id == dest_id)
                {
                    // send average time

                    avg_travel_time = ride->avg_time; // guardando el tiempo medio de viaje
                    printf("Abriendo archivo para escritura\n.");
                    fd = open("myfifo", O_WRONLY); // Abriendo archivo para escritura
                    if (write(fd, &avg_travel_time, sizeof(float)) == -1)
                    {
                        return 2;
                    }
                    close(fd); // Cerramos el archivo de envio
                    found = true;
                    break;
                }
                infile_pos = ride->next_source_id;

            } while (infile_pos != -1);

            if (!found)
            {
                avg_travel_time = -1.0; // guardando -1
                printf("Abriendo archivo para escritura. \n");
                fd = open("myfifo", O_WRONLY); // Abriendo archivo para escritura
                if (write(fd, &avg_travel_time, sizeof(float)) == -1)
                {
                    return 2;
                }
                close(fd); // Cerramos el archivo de envio
            }

            free(ride);
        }
    }//Hasta aquí va el while
        fclose(bfp);
        fclose(source_id_table_file);
}
