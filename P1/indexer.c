/*
 * Indexes the binary file of structures by source ID. Produces the indexed binary file
 * and a binary file containing a table of the first positions for each ID.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ride.h"
#define TABLE_SIZE 1200

int main()
{
    FILE *bfp = fopen("rides.bin", "rb+");
    Ride ride;

    int heads_id_source[TABLE_SIZE]; // heads of the linked lists
    int tails_id_source[TABLE_SIZE]; // tails of the linked lists
    int current_pos = 0;             // current file position

    // initalizes the heads and tails in -1
    for (int i = 0; i < 1200; i++)
    {
        tails_id_source[i] = -1;
        heads_id_source[i] = -1;
    }

    while (fread(&ride, sizeof(Ride), 1, bfp)) // reads one row at a time and puts it in a Ride struct
    {
        int current_id_source = ride.id_source;

        if (tails_id_source[current_id_source] == -1) // new linked list
        {
            tails_id_source[current_id_source] = current_pos;
            heads_id_source[current_id_source] = current_pos;
        }
        else // append to linked list
        {
            Ride old_tail;                                            // previous tail
            fseek(bfp, tails_id_source[current_id_source], SEEK_SET); // moves to the infile position on the old tail
            fread(&old_tail, sizeof(Ride), 1, bfp);                   // reads the structure
            old_tail.next_id_source = current_pos;                    // set next source id
            fseek(bfp, -sizeof(struct Ride), SEEK_CUR);               // moves back to where the old tail was located
            fwrite(&old_tail, sizeof(Ride), 1, bfp);                  // write old tail
            tails_id_source[current_id_source] = current_pos;         // put new tail in the tails array
            fseek(bfp, current_pos + sizeof(Ride), SEEK_SET);         // set infile position back were it was
        }

        current_pos = ftell(bfp); // change current pos
    }

    FILE *heads_fp = fopen("source_id_table.bin", "wb");
    fwrite(&heads_id_source, sizeof(heads_id_source), 1, heads_fp);

    // close files
    fclose(heads_fp);
    fclose(bfp);
}
