// TODO: Clean includes
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include "ride.h"
#define PORT 8080

// #include <sys/types.h>
// #include <netdb.h>
// #include <sys/time.h>
// #include <time.h>
// #include <sys/stat.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <ncurses.h>

int goption(int min, int max);

int main()
{
    int server_fd;
    struct sockaddr_in server_addr;

    /* Initialize socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket failed.");
        exit(EXIT_FAILURE);
    }

    printf("Init socket.\n");

    /* Configure socket address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr));
    bzero(server_addr.sin_zero, 8);

    printf("Socket address configured.\n");

    /* Connect to server socket */
    if (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed.");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    Ride ride;
    ride.source_id = -1;
    ride.dest_id = -1;
    ride.hour = -1;

    int option;
    bool exit = false;

    /* Menu prompt loop */
    while (!exit)
    {

        printf("\n");
        printf("Por favor seleccione una de las siguientes opciones:\n");
        printf("1. Ingresar origen\n");
        printf("2. Ingresar destino\n");
        printf("3. Ingresar hora\n");
        printf("4. Buscar tiempo de viaje medio\n");
        printf("5. Salir\n");

        option = goption(1, 5);

        switch (option)
        {

        case 1:
            printf("Ingrese ID del origen: ");
            ride.source_id = goption(1, 1160);
            break;
        case 2:
            printf("Ingrese ID de destino: ");
            ride.dest_id = goption(1, 1160);
            break;
        case 3:
            printf("Ingrese hora del dia: ");
            ride.hour = goption(0, 23);
            break;
        case 4:
            if (ride.source_id == -1 || ride.dest_id == -1 || ride.hour == -1)
            {
                printf("Ingrese todos los datos.\n");
                break;
            }
            // TODO: Check all the info was sended

            printf("Sended ride information to server\n");

            send(server_fd, &ride, sizeof(ride), 0);
            read(server_fd, &ride.avg_time, sizeof(ride.avg_time));

            if (ride.avg_time < 0)
                printf("No se han un viaje con las caracteristicas deseadas.\n");
            else
                printf("El tiempo medio de viaje es: %0.2f.\n", ride.avg_time);

            // initscr(); // Init alternative screen
            // printw("\n Presione cualquier tecla para continuar. \n");
            // refresh();
            // getch();  // Press any key
            // endwin(); // End alternative screen
            ride.source_id = -1;
            ride.dest_id = -1;
            ride.hour = -1;
            break;

        case 5:
            // Sending -1 to close the program
            ride.source_id = -1;
            exit = true;
            send(server_fd, &ride, sizeof(ride), 0);
            close(server_fd);
            break;
        }
    }

    return 0;
}

/* Get number from stdin between min and max. */
int goption(int min, int max)
{
    char input[100];
    int option;
    char *remaining;
    for (;;)
    {
        fgets(input, sizeof(input), stdin);
        option = strtol(input, &remaining, 10);

        if (remaining[0] == '\n')
            if (option >= min && option <= max)
                break;
            else
                printf("Inserte un número entre %d y %d.\n", min, max);
        else
            printf("Inserte una opción adecuada.\n");
    }
    return option;
}
