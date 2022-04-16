/*
 * This program reads the travel_data.csv file, turns each row into a Ride structure
 * and then writes those structures into a binary file named rides.bin
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ride.h"

void csv_to_bin()
{

    FILE *fp = fopen("../data/travel_data.csv", "r");

    if (fp == NULL)
    {
        printf("Can't open file\n");
        exit(-1);
    }
    else
    {
        FILE *bfp = fopen("../data/rides.bin", "wb");
        char row[1024];

        fgets(row, 1024, fp); // dismiss column headers

        while (fgets(row, 1024, fp)) // process each row
        {
            int source_id;
            int dest_id;
            int hour;
            float avg_time;

            // parse to appropiate types
            source_id = atoi(strtok(row, ","));
            dest_id = atoi(strtok(NULL, ","));
            hour = atoi(strtok(NULL, ","));
            avg_time = atof(strtok(NULL, ","));

            Ride ride = {source_id, dest_id, hour, avg_time, -1}; // build struct
            fwrite(&ride, sizeof(Ride), 1, bfp);                  // write struct to bin file
        }
        fclose(bfp);
        fclose(fp);
    }
}
