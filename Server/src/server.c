#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ride.h"
#define PORT 8080
#define BACKLOG 32
#define SA struct sockaddr_in
#define TABLE_SIZE 1200

// TODO: Handle server shutdown

float search_ride(Ride ride, int client_fd, int *source_id_table, FILE *rides_data_file);
void log_search(char *client_ip, int source_id, int dest_id, int hour);

int main()
{
    /* Initialize data */
    FILE *rides_data_file = fopen("data/processed/rides.bin", "rb");
    FILE *source_id_table_file = fopen("data/processed/source_id_table.bin", "rb");

    int source_id_table[TABLE_SIZE];

    if (rides_data_file == NULL || source_id_table_file == NULL)
    {
        perror("Can't open rides data files.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TABLE_SIZE; i++)
        source_id_table[i] = -1;
    fread(&source_id_table, sizeof(source_id_table), 1, source_id_table_file);

    /* Initialize socket */
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(client_addr);

    /* Configure socket address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bzero(server_addr.sin_zero, 8);

    /* Create and configure socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    if (bind(server_fd, (SA *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed.");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, BACKLOG) < 0)
    {
        perror("Listen failed.");
        exit(EXIT_FAILURE);
    }

    printf("Initialized server.\n");

    Ride ride;
    char client_ip[INET_ADDRSTRLEN];

    /* Wait for clients */
    for (;;)
    {
        client_fd = accept(server_fd, (SA *)&client_addr, &addrlen);

        printf("socket file descriptor: %d.\n", client_fd);

        if (client_fd < 0)
        {
            perror("Failed to accept connection.");
            exit(EXIT_FAILURE);
        }

        /* Get client IP address */
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);

        if (fork() == 0)
        {
            /* search prompt loop */
            for (;;)
            {
                /* Get travel info */
                read(client_fd, &ride, sizeof(ride));

                /* Close connection */
                if (ride.source_id == -1)
                {
                    close(client_fd);
                    break;
                }

                ride.avg_time = search_ride(
                    ride,
                    client_fd,
                    source_id_table,
                    rides_data_file);

                /* Send average travel time */
                send(client_fd, &(ride.avg_time), sizeof(ride.avg_time), 0);

                log_search(
                    client_ip,
                    ride.source_id,
                    ride.dest_id,
                    ride.hour);
            }
        }
    }
}

/* Returns the mean travel time given the ride informationor -1 if the ride was not found. */
float search_ride(Ride ride, int client_fd, int *source_id_table, FILE *rides_data_file)
{
    if (source_id_table[ride.source_id] == -1)
    {
        return -1.0;
    }

    Ride temp_ride;
    int infile_pos = source_id_table[ride.source_id];

    /* Search through the linked list of the source ID */
    do
    {
        fseek(rides_data_file, infile_pos, SEEK_SET);
        fread(&temp_ride, sizeof(Ride), 1, rides_data_file);
        if (temp_ride.hour == ride.hour && temp_ride.dest_id == ride.dest_id)
        {
            return temp_ride.avg_time;
        }
        infile_pos = temp_ride.next_source_id;

    } while (infile_pos != -1);

    return -1;
}

/* Saves the search information in the log file */
void log_search(char *client_ip, int source_id, int dest_id, int hour)
{
    FILE *log_file = fopen("log/searchs.log", "a+");
    if (log_file == NULL)
    {
        perror("Can't open log file");
        exit(EXIT_FAILURE);
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(log_file,
            "[Fecha: %d:%02d:%02d %02d:%02d:%02d] Cliente [%s], [so_id: %d - dest_id: %d - hour: %d]\n",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec,
            client_ip,
            source_id,
            dest_id,
            hour);
    fclose(log_file);
}