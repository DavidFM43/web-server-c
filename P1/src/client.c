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
#define PORT 8080

void Menu();

int main()
{
    bool flag = true;

    // ride variables
    int origin_id;
    int destination_id;
    int hour;
    float avg_travel_time;

    // sockets variables
    int arrSend[3] = {-2, -2, -2};
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("%s", "Bienvenido\n");

    while (flag)
    {

        Menu();
        char s[128];
        char buf[100];
        char choice;
        char *p;
        while (fgets(buf, sizeof buf, stdin))
        {
            choice = buf[0];
            if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5')
            {
                if (buf[1] == '\n')
                    break;
                else
                    printf("Introduzca una entrada adecuada.\n");
            }
            else
                printf("Introduzca una entrada adecuada.\n");
        }
        switch (choice)
        {
        case '1':
            while (true)
            {
                printf("Ingrese ID del origen: ");
                while (fgets(s, sizeof(s), stdin))
                {
                    origin_id = strtol(s, &p, 10);
                    if (p == s || *p != '\n')
                    {
                        printf("Inserte una entrada adecuada.\nIngrese ID del origen: ");
                    }
                    else
                        break;
                }
                if (origin_id >= 1 && origin_id <= 1160)
                {
                    arrSend[0] = origin_id; // saving origin_id for then send
                    break;
                }
                printf("Seleccione un ID entre 1 y 1160.\n");
            }
            break;
        case '2':
            while (true)
            {
                printf("Ingrese ID de destino: ");
                while (fgets(s, sizeof(s), stdin))
                {
                    destination_id = strtol(s, &p, 10);
                    if (p == s || *p != '\n')
                    {
                        printf("Inserte una entrada adecuada.\nIngrese ID de destino: ");
                    }
                    else
                        break;
                }
                if (destination_id >= 1 && destination_id <= 1160)
                {
                    arrSend[1] = destination_id; // saving destination_id for then send
                    break;
                }
                printf("Seleccione un ID entre 1 y 1160.\n");
            }
            break;
        case '3':
            while (true)
            {
                printf("Ingrese hora del dia: ");
                while (fgets(s, sizeof(s), stdin))
                {
                    hour = strtol(s, &p, 10);
                    if (p == s || *p != '\n')
                    {
                        printf("Inserte una entrada adecuada.\nIngrese hora del dia: ");
                    }
                    else
                        break;
                }
                if (hour >= 0 && hour <= 23)
                {
                    arrSend[2] = hour; // saving hour for then send
                    break;
                }
                printf("Seleccione una hroa entre 0 y 23.\n");
            }
            break;
        case '4':
            if (arrSend[0] == -2 || arrSend[1] == -2 || arrSend[2] == -2)
            { // incomplete data
                printf("Por favor ingrese todos los datos de nuevo.\n");
            } else {
                send(sock, arrSend, sizeof(arrSend), 0); // send data
                printf("Se han enviado los datos (cliente). \n");
                read(sock, &avg_travel_time, sizeof(avg_travel_time)); // recieve travel time
                printf("Se ha recibido el dato (cliente). \n");
                if(avg_travel_time == -1.00)
                    printf("No se han encontrado coincidencias.\n");
                else
                    printf("El tiempo medio de viaje es: %0.2f.\n", avg_travel_time);
                arrSend[0] = -2;
                arrSend[1] = -2;
                arrSend[2] = -2;
                send(sock, arrSend, sizeof(arrSend), 0);
            }
            break;
        case '5':
            // sending -1 to close the program
            arrSend[0] = -1;
            arrSend[1] = -1;
            arrSend[2] = -1;
            send(sock, arrSend, sizeof(arrSend), 0);
            flag = false;
            close(client_fd);
            break;
        }
    }

    return 0;
}

void Menu()
{
    printf("%s", "\nPor favor seleccione una de las siguientes opciones:\n");
    printf("%s", "1. Ingresar origen\n2. Ingresar destino\n");
    printf("%s", "3. Ingresar hora\n4. Buscar tiempo de viaje medio\n");
    printf("%s", "5. Salir\n\n");
}
