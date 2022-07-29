/*
 * This program reads the travel_data.csv file, turns each row into a Ride structure
 * and then writes those structures into a binary file named rides.bin
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ride.h"

int main()
{

    FILE *fp = fopen("data/raw/travel_data.csv", "r");

    if (fp == NULL)
    {
        printf("Can't open travel data file.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        FILE *bfp = fopen("data/processed/rides.bin", "wb");
        if (bfp == NULL)
        {
            printf("Can't create file.\n");
            exit(EXIT_FAILURE);
        }
        char row[1024];

        /* Dismiss column headers */
        fgets(row, 1024, fp);

        while (fgets(row, 1024, fp))
        {
            int source_id;
            int dest_id;
            int hour;
            float avg_time;

            source_id = atoi(strtok(row, ","));
            dest_id = atoi(strtok(NULL, ","));
            hour = atoi(strtok(NULL, ","));
            avg_time = atof(strtok(NULL, ","));

            Ride ride = {source_id, dest_id, hour, avg_time, -1};
            fwrite(&ride, sizeof(Ride), 1, bfp);
        }
        fclose(bfp);
        fclose(fp);
    }
    return 0;
}
