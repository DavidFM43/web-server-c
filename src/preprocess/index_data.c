/*
 * Indexes the binary file of structures by source ID. Produces the indexed binary file
 * and a binary file containing a table of the first infile positions for each ID.
 */
#include <stdio.h>
#include <stdlib.h>
#include "../ride.h"
#define TABLE_SIZE 1200

int main()
{
    FILE *rides_file = fopen("data/processed/rides.bin", "rb+");
    if (rides_file == NULL)
    {
        perror("Can't open rides file.");
        exit(EXIT_FAILURE);
    }

    Ride ride;

    int ll_heads[TABLE_SIZE];
    int ll_lasts[TABLE_SIZE];
    int infile_pos = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ll_lasts[i] = -1;
        ll_heads[i] = -1;
    }

    /* Reads the file and buils linked lists with coinciding
       source ids by updating the next_source_id field */
    while (fread(&ride, sizeof(Ride), 1, rides_file))
    {
        int source_id = ride.source_id;

        /* New linked list */
        if (ll_lasts[source_id] == -1)
        {
            ll_lasts[source_id] = infile_pos;
            ll_heads[source_id] = infile_pos;
        }
        else
        {
            Ride old_tail;

            /* Update linked list tail*/
            fseek(rides_file, ll_lasts[source_id], SEEK_SET);
            fread(&old_tail, sizeof(Ride), 1, rides_file);
            old_tail.next_source_id = infile_pos;
            fseek(rides_file, -sizeof(Ride), SEEK_CUR);
            fwrite(&old_tail, sizeof(Ride), 1, rides_file);
            ll_lasts[source_id] = infile_pos;
            fseek(rides_file, infile_pos + sizeof(Ride), SEEK_SET);
        }

        infile_pos = ftell(rides_file);
    }

    /* Save linked list heads to file */
    FILE *heads_fp = fopen("data/processed/source_id_table.bin", "wb");
    fwrite(&ll_heads, sizeof(ll_heads), 1, heads_fp);

    fclose(heads_fp);
    fclose(rides_file);

    return 0;
}
