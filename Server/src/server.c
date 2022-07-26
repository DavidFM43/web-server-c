#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#define PORT 8080
#define BACKLOG 3
#define TABLE_SIZE 1200

#include "ride.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main()
{

    /* Initialize data */
    FILE *bfp = fopen("data/rides.bin", "rb");
    FILE *source_id_table_file = fopen("data/source_id_table.bin", "rb");
    FILE *f = fopen("x.log", "w");
    if (bfp == NULL || source_id_table_file == NULL || f == NULL)
    {
        printf("Can't open files");
        exit(EXIT_FAILURE);
    }
    // REFACTOR: This part does not look nice
    int source_id_table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        source_id_table[i] = -1;
    }
    fread(&source_id_table, sizeof(source_id_table), 1, source_id_table_file);

    /* Initialize socket */
    int serverfd, clientfd;
    struct sockaddr_in server, client;
    int addrlen = sizeof(client);

    /* Configure socket address */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(PORT);
    bzero(server.sin_zero, 8);

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (bind(serverfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed.");
        exit(EXIT_FAILURE);
    }
    if (listen(serverfd, BACKLOG) < 0)
    {
        perror("listen failed.");
        exit(EXIT_FAILURE);
    }

    /* Receive clients and search procedure */
    int source_id;
    int dest_id;
    int hour;
    float avg_travel_time;
    // REFACTOR: Why not initialize and define at once
    int infile_pos;
    bool found;
    int arrArrival[3];
    pid_t pid;
    time_t t;
    /* REFACTOR: It is not clear right away the purpose of the while loop
     * Maybe change for recursive function?
     */
    while (true)
    {
        if ((clientfd = accept(serverfd, (struct sockaddr *)&client, &addrlen)) < 0)
        {
            perror("failed to accept connection.");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == 0)
        {
            while (true)
            {
                close(serverfd);
                // receives data from user interface process

                read(clientfd, arrArrival, sizeof(arrArrival)); // receive data
                // sleep(5);
                time(&t);
                fprintf(f, "[Fecha %s] Cliente [%s] [%d - %d]\n", ctime(&t), inet_ntoa(client.sin_addr), arrArrival[0], arrArrival[1]); // log file info
                printf("\n Se leyeton los datos (servidor). \n");

                if (arrArrival[0] == -1) // program termination flag
                {
                    // close files
                    fclose(bfp);
                    fclose(source_id_table_file);
                    close(clientfd);
                    shutdown(serverfd, SHUT_RDWR);
                    return 0;
                }

                // save arrival data on corresponding variables
                source_id = arrArrival[0];
                dest_id = arrArrival[1];
                hour = arrArrival[2];
                Ride *ride = malloc(sizeof(Ride)); // allocate memory for Ride struct
                if (ride == NULL)
                    exit(-1);

                // start search procedure
                if (source_id_table[source_id] == -1) // no rides with that source id
                {
                    avg_travel_time = -1.00;                                      // NA flag
                    // TODO: Validate the send call
                    send(clientfd, &avg_travel_time, sizeof(avg_travel_time), 0); // send result using socket
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
                            avg_travel_time = ride->avg_time;                             // save average travel time
                            send(clientfd, &avg_travel_time, sizeof(avg_travel_time), 0); // send result using socket
                            printf("\n Se ha enviado el dato (servidor). \n");
                            found = true;
                            break;
                        }
                        infile_pos = ride->next_source_id;

                    } while (infile_pos != -1);

                    if (!found)
                    {
                        avg_travel_time = -1.0;                                       // NA flag
                        send(clientfd, &avg_travel_time, sizeof(avg_travel_time), 0); // send result using socket
                        printf("\n Se ha enviado el dato (servidor). \n");
                    }
                }
                free(ride);                                     // free memory from ride struct
                read(clientfd, arrArrival, sizeof(arrArrival)); // receive flag through the socket
            }
            fclose(f);
        }
    }
    close(clientfd);
}
