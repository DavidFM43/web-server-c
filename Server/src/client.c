// TODO: Clean includes
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include "ride.h"
#define PORT 8080

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
#include <ncurses.h>

int gchoice(int min, int max);

int main()
{
    /* Initialize socket */
    int socketfd;
    struct sockaddr_in server;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Socket failed.");
        exit(EXIT_FAILURE);
    }

    /* Configure socket address */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    bzero(server.sin_zero, 8);

    /* Connect to server socket */
    if (connect(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed.");
        exit(EXIT_FAILURE);
    }

    Ride ride;
    int choice;

    /* Menu prompt loop */
    for (;;)
    {
        ride.source_id = -1;
        ride.dest_id = -1;
        ride.hour = -1;

        printf("Por favor seleccione una de las siguientes opciones:\n");
        printf("1. Ingresar origen\n");
        printf("2. Ingresar destino\n");
        printf("3. Ingresar hora\n");
        printf("4. Buscar tiempo de viaje medio\n");
        printf("5. Salir\n");

        choice = gchoice(1, 5);

        switch (choice)
        {

        case '1':
            printf("Ingrese ID del origen: ");
            ride.source_id = gchoice(1, 1160);
            break;
        case '2':
            printf("Ingrese ID de destino: ");
            ride.dest_id = gchoice(1, 1160);
            break;
        case '3':
            printf("Ingrese hora del dia: ");
            ride.hour = gchoice(0, 23);
            break;
        case '4':
            if (ride.source_id == -1 || ride.dest_id == -1 || ride.hour == -1)
            {
                printf("Ingrese todos los datos.\n");
                break;
            }
            send(socketfd, &ride, sizeof(ride), 0);
            read(socketfd, &ride.avg_time, sizeof(ride.avg_time));

            if (ride.avg_time < 0)
                printf("No se han un viaje con las caracteristicas deseadas.\n");
            else
                printf("El tiempo medio de viaje es: %0.2f.\n", ride.avg_time);

            // send(socketfd, arrSend, sizeof(arrSend), 0); // Data send to the server using socket

            initscr(); // Init alternative screen
            printw("\n Presione cualquier tecla para continuar. \n");
            refresh();
            getch();  // Press any key
            endwin(); // End alternative screen
            break;

        case '5':
            // Sending -1 to close the program
            arrSend[0] = -1;
            arrSend[1] = -1;
            arrSend[2] = -1;
            send(socketfd, arrSend, sizeof(arrSend), 0); // Send flag
            close(socketfd);
            break;
        }
    }

    return 0;
}

/* Get number from stdin between min and max. */
int gchoice(int min, int max)
{
    char input[100];
    int choice;
    char *remaining;
    for (;;)
    {
        fgets(input, sizeof(input), stdin);
        choice = strtol(input, &remaining, 10);

        if (remaining[0] == '\n')
            if (choice >= min && choice <= max)
                break;
            else
                printf("Inserte un número entre %d y %d.\n", min, max);
        else
            printf("Inserte una opcion adecuada.\n");
    }
    return choice;
}
