/*
 * This program reads the travel_data.csv file, turns each row into a Ride structure
 * and then writes those structures into a binary file named rides.bin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ride
{
    int id_source;
    int id_dest;
    int hour;
    float avg_time;

    struct Ride *next_id_source;
    struct Ride *next_id_dest;
    struct Ride *next_source;
    struct Ride *next_avg;
};

void main()
{
    FILE *fp = fopen("test_travel_data.csv", "r");

    if (fp == NULL)
    {
        printf("Can't open file\n");
        exit(1);
    }
    else
    {
        FILE *bfp = fopen("rides.bin", "wb");
        char row[1024];

        fgets(row, 1024, fp); // dismiss column headers

        while (fgets(row, 1024, fp))
        {
            char *value;
            int id_source;
            int id_dest;
            int hour;
            float avg_time;

            id_source = atoi(strtok(row, ","));
            id_dest = atoi(strtok(NULL, ","));
            hour = atoi(strtok(NULL, ","));
            avg_time = atof(strtok(NULL, ","));

            struct Ride ride = {id_source, id_dest, hour, avg_time};
            fwrite(&ride, sizeof(struct Ride), 1, bfp);
        }
        fclose(bfp);
        fclose(fp);
    }
}