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

int main(){



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
    for (int i = 0; i < 1200; i++){
        source_id_table[i] = -1;
    } 
    
    // load source id table
    fread(&source_id_table, sizeof(source_id_table), 1, source_id_table_file);

    // seach parameters
    int source_id;
    int dest_id;
    int hour;
    Ride *ride = malloc(sizeof(Ride));
    int infile_pos;
    bool found;

    // Inicializando la FIFO, el arreglo de recibido y paquete de envio
    int arrArrival[3];
    int fd;
    float avg_travel_time;

    // create pipe
    if (mkfifo("myfifo", 0777) == -1)
    { // creating fifo file
        if (errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    printf("Abriendo archivo para lectura...\n");
    fd = open("myfifo", O_RDONLY); //Abrir el archivo para lectura
    if (fd == -1)
    {
        return 1;
    }
    if (read(fd, &arrArrival, sizeof(arrArrival)) == -1){ //leyendo
            return 2;
        }

    
    source_id = arrArrival[0];
    dest_id = arrArrival[1];
    hour = arrArrival[2];
    printf("Aquí ya esta leido\n");
    close(fd);//Cierre del archivo para lectura
    
    printf("%d %d %d ", source_id, dest_id, hour); 
    // seach procedure
    if (source_id_table[source_id] == -1)
    {
        // send NA
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
                // printf("Tiempo de viaje medio %f\n\n", ride->avg_time);

                avg_travel_time = ride->avg_time; // guardando el tiempo medio de viaje
                printf("Abriendo archivo para escritura\n.");
                fd = open("myfifo", O_WRONLY); //Abriendo archivo para escritura
                if(write(fd, &avg_travel_time, sizeof(float)) == -1){
                    return 2;
                }
                close(fd); //Cerramos el archivo de envio 
                found = true;
                break;
            }
            infile_pos = ride->next_source_id;

        } while (infile_pos != -1);

        if (!found)
        {
            // send NA
            // printf("NA.\n\n");
        }

        free(ride);

        // close when program ends
        fclose(bfp);
        fclose(source_id_table_file);
    }
}
