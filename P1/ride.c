#include 
void print_ride(Ride *ride)
{
    // TODO null pointer safety
    printf("Source: %d\n", ride->source_id);
    printf("Id_dest: %d\n", ride->dest_id);
    printf("Hour: %d\n", ride->hour);
    printf("Average time : %0.2f\n", ride->avg_time);

}