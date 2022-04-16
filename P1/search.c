#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ride.h"
#define TABLE_SIZE 1200

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main()
{

    // open files
    FILE *bfp = fopen("data/travel_data.bin", "rb");
    FILE *source_id_table_file = fopen("data/source_id_table.bin", "rb");

    if (bfp == NULL || source_id_table_file == NULL)
    {
        printf("Can't open files");
        exit(-1);
    }

    // initialize table
    int source_id_table[TABLE_SIZE];
    for (int i = 0; i < 1200; i++)
        source_id_table[i] = -1;
    fread(&source_id_table, sizeof(source_id_table), 1, source_id_table_file);

    // seach parameters
    int source_id;
    int dest_id;
    int hour;
    Ride *ride = malloc(sizeof(Ride));
    int infile_pos;
    bool found;
    int arrSend[3];

    // create pipe
    if (mkfifo("myfifo", 0666) == -1)
    { // creating fifo file
        if (errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
    }

    int fd = open("myfifo", O_RDONLY); // Inicializando la ruta y haciendo la apertura para escribir
    if (fd == -1)
    {
        return 1;
    }

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
