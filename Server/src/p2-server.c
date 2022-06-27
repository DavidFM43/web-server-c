#include "ride.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#define PORT 8080
#define TABLE_SIZE 1200

int main(int argc, char const* argv[])
{
    // open files
    FILE *bfp = fopen("data/rides.bin", "rb");
    FILE *source_id_table_file = fopen("data/source_id_table.bin", "rb");
    FILE *f = fopen("x.log", "w"); // log file
    if (bfp == NULL || source_id_table_file == NULL || f == NULL)
    {
        printf("Can't open files");
        exit(-1);
    }

    // initialize table
    int source_id_table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        source_id_table[i] = -1;
    }

    // load source id table
    fread(&source_id_table, sizeof(source_id_table), 1, source_id_table_file);

    // search variables
    int source_id;
    int dest_id;
    int hour;
    float avg_travel_time;
    int infile_pos;
    bool found;
    
    // sockets variables
    int arrArrival[3];
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
 
    //others
    time_t t;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed\n");
        exit(EXIT_FAILURE);
    }
 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen\n");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        // receives data from user interface process

        read(new_socket, arrArrival, sizeof(arrArrival)); // receive data
        time(&t);
        fprintf(f, "[Fecha %s] Cliente [%s] [%d - %d]\n", ctime(&t), inet_ntoa(address.sin_addr), arrArrival[0], arrArrival[1]); // log file info
        printf("\n Se leyeton los datos (servidor). \n");

        if (arrArrival[0] == -1) // program termination flag
        {
            // close files
            fclose(bfp);
            fclose(source_id_table_file);
            close(new_socket);
            shutdown(server_fd, SHUT_RDWR);
            return 0;
        } 

        // save arrival data on corresponding variables
        source_id = arrArrival[0];
        dest_id = arrArrival[1];
        hour = arrArrival[2];
        Ride *ride = malloc(sizeof(Ride)); // allocate memory for Ride struct
        if(ride == NULL) exit(-1);

        // start search procedure
        if (source_id_table[source_id] == -1) // no rides with that source id
        {
            avg_travel_time = -1.00;        // NA flag
            send(new_socket, &avg_travel_time, sizeof(avg_travel_time), 0); // send result using socket
            printf("\n Se ha enviado el dato (servidor). \n");
            break;
        }
        else
        {
            infile_pos = source_id_table[source_id];
            found = false;
            do // search through the linked list of the source ID
            {
                fseek(bfp, infile_pos, SEEK_SET);
                fread(ride, sizeof(Ride), 1, bfp);
                if (ride->hour == hour && ride->dest_id == dest_id) // checks criteria
                {
                    avg_travel_time = ride->avg_time; // save average travel time
                    send(new_socket, &avg_travel_time, sizeof(avg_travel_time), 0); // send result using socket
                    printf("\n Se ha enviado el dato (servidor). \n");
                    found = true;
                    break;
                }
                infile_pos = ride->next_source_id;

            } while (infile_pos != -1);

            if (!found)
            {
                avg_travel_time = -1.0;        // NA flag
                send(new_socket, &avg_travel_time, sizeof(avg_travel_time), 0); // send result using socket
                printf("\n Se ha enviado el dato (servidor). \n");
            }
        }
        free(ride); // free memory from ride struct
        read(new_socket, arrArrival, sizeof(arrArrival)); // receive flag through the socket
    }
    fclose(f);
}
