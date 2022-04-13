#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ride.h"

void print_ride(struct Ride ride);

int main()
{
    FILE *bfp = fopen("rides.bin", "rb");
    FILE *heads_fp = fopen("source_id_heads.bin", "rb");
    long heads_id_source[1200] = {0};
    int id_tosearch;
    int infile_pos;
    struct Ride ride;

    for (int i = 0; i < 1200; i++)
    {
        heads_id_source[i] = -1;
    }

    if (!heads_fp)
    {
        printf("Can't open file.\n");
        exit(-1);
    }

    fread(&heads_id_source, sizeof(heads_id_source), 1, heads_fp);

    printf("Ingrese ID del origen:");
    scanf("%d", &id_tosearch);

    if (heads_id_source[id_tosearch] == -1)
    {
        printf("No rides with desired source ID.\n");
    }
    else
    {
        infile_pos = heads_id_source[id_tosearch];
        do
        {
            fseek(bfp, infile_pos, SEEK_SET);
            fread(&ride, sizeof(struct Ride), 1, bfp);
            print_ride(ride);
            infile_pos = ride.next_id_source;
        } while (infile_pos != -1);
    }

    fclose(bfp);
    fclose(heads_fp);
}

void print_ride(struct Ride ride)
{
    printf("Id_source: %d\n", ride.id_source);
    printf("Id_dest: %d\n", ride.id_dest);
    printf("Hour: %d\n", ride.hour);
    printf("Average time : %f\n", ride.avg_time);
    printf("next: %d\n\n", ride.next_id_source);
}