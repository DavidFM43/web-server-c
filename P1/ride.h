// #ifndef RIDE_H
// #define RIDE_H

struct Ride
{
    int id_source;
    int id_dest;
    int hour;
    float avg_time;

    long next_id_source;
    long next_id_dest;
    long next_hour;
    long next_avg_time;
};

void print_ride(struct Ride ride)
{
    printf("Id_source: %d\n", ride.id_source);
    printf("Id_dest: %d\n", ride.id_dest);
    printf("Hour: %d\n", ride.hour);
    printf("Average time : %0.2f\n", ride.avg_time);
}

// #endif
