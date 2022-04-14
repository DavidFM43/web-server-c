#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ride.h"


int main()
{
    FILE *bfp = fopen("rides.bin", "rb");
    FILE *heads_fp = fopen("source_id_heads.bin", "rb");
    long heads_id_source[1200];
    int id_tosearch;
    int infile_pos;
    Ride ride;

    for (int i = 0; i < 1200; i++)
    {
        heads_id_source[i] = -1;
    }

    if (!heads_fp)
    {
        printf("Can't open firts poisitions file.\n");
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
            fread(&ride, sizeof(Ride), 1, bfp);
            print_ride(&ride);
            infile_pos = ride.next_id_source;

        } while (infile_pos != -1);
    }

    fclose(bfp);
    fclose(heads_fp);
}
