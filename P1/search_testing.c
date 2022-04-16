#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ride.h"
#define TABLE_SIZE 1200

int main()
{

    // open files
    FILE *bfp = fopen("rides.bin", "rb");
    FILE *source_id_table_file = fopen("source_id_table.bin", "rb");
    if (source_id_table_file == NULL || bfp == NULL)
    {
        printf("Can't open files.\n");
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

    do
    {
        // menu prompt
        printf("Ingrese ID del origen: ");
        scanf("%d", &source_id);
        printf("Ingrese ID del destino: ");
        scanf("%d", &dest_id);
        printf("Ingrese la hora: ");
        scanf("%d", &hour);

        if (source_id_table[source_id] == -1)
        {
            printf("NA.\n");
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
                    printf("Tiempo de viaje medio %f\n\n", ride->avg_time);
                    found = true;
                }
                infile_pos = ride->next_source_id;

            } while (infile_pos != -1);

            if (!found)
            {
                printf("NA.\n\n");
            }
        }
    } while (true);

    free(ride);
    fclose(bfp);
    fclose(source_id_table_file);
}
