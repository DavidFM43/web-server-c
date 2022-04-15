#ifndef RIDE_H
#define RIDE_H

typedef struct Ride
{
    int source_id;
    int dest_id;
    int hour;
    float avg_time;
    int next_source_id;
} Ride;

#endif
