#ifndef RIDE_H
#define RIDE_H

typedef struct Ride {
    int id_source;
    int id_dest;
    int hour;
    float avg_time;
    int next_id_source;
} Ride;


void print_ride(Ride *ride)
{
    // TODO null pointer safety
    printf("Id_source: %d\n", ride->id_source);
    printf("Id_dest: %d\n", ride->id_dest);
    printf("Hour: %d\n", ride->hour);
    printf("Average time : %0.2f\n", ride->avg_time);

}

#endif
