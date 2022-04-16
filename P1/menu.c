#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
void Menu();

int main()
{
	int choice = 0;
	int c;

	int origin_id;
	int destination_id;
	int hour;
	float avg_travel_time;
	// Inicializando la FIFO, el arreglo de envio y ans de recibido
	int arrSend[3];
	int fd;

	if (mkfifo("myfifo", 0777) == -1) // creating fifo file
	{ 
		if (errno != EEXIST)
		{
			printf("Could not create fifo file\n");
			return 1;
		}
	}

	printf("%s", "Bienvenido\n");

	while (true)
	{

		Menu();

		while (scanf("%d", &choice) != 1) // handling of  wrong input type
		{
			while (!isspace(c = getchar()));
			ungetc(c, stdin);
			printf("Seleccione una opción adecuada.\n\n");
			Menu();
			continue;
		}

		if (choice == 1)
		{
			while (true)
			{
				printf("Ingrese ID del origen:");
				while (scanf("%d", &origin_id) != 1) // handling of  wrong input type
				{
					while (!isspace(c = getchar()));
					ungetc(c, stdin);
					printf("Seleccione un ID entre 1 y 1160.\n");
					continue;
				}
				if (origin_id >= 1 && origin_id <= 1160)
				{
					arrSend[0] = origin_id; // saving origin_id for then send
					break;
				}
				printf("Seleccione un ID entre 1 y 1160.\n");
			}
		}
		else if (choice == 2)
		{
			while (true)
			{
				printf("Ingrese ID del destino:");
				while (scanf("%d", &destination_id) != 1) // handling of  wrong input type
				{
					while (!isspace(c = getchar()));
					ungetc(c, stdin);
					printf("Seleccione un ID entre 1 y 1160.\n");
					continue;
				}
				if (destination_id >= 1 && destination_id <= 1160)
				{
					arrSend[1] = destination_id; // saving destination_id for then send
					break;
				}
				printf("Seleccione un ID entre 1 y 1160. ");
			}
		}
		else if (choice == 3)
		{
			while (true)
			{
				printf("Ingrese hora del día:");
				while (scanf("%d", &hour) != 1) // handling of  wrong input type
				{
					while (!isspace(c = getchar()));
					ungetc(c, stdin);
					printf("Seleccione una hora entre 0 y 23.\n");
					continue;
				}
				if (hour >= 0 && hour <= 23)
				{
					arrSend[2] = hour; // saving hour for then send
					break;
				}
				printf("Seleccione una hora entre 0 y 23.\n");
			}
		}
		else if (choice == 4)
		{
			printf("Abriendo para escribir.\n ");
			fd = open("myfifo", O_WRONLY); // Abrir el archivo para escribir
			if (fd == -1)
			{
				return 1; // can't open pipe
			}

			if (write(fd, &arrSend, sizeof(arrSend)) == -1)
			{			  // Envia el mensaje
				return 2; // can't write from pipe
			}

			close(fd);

			printf("Abriendo para leer.\n");
			// Apertura para leer el tiempo medio de viaje
			fd = open("myfifo", O_RDONLY); // Abrir el archivo para lectura
			if (fd == -1)
			{
				return 1; // can't open pipe
			}
			if (read(fd, &avg_travel_time, sizeof(float)) == -1)
			{			  // leyendo
				return 2; // can't read from pipe
			}
			else
			{
				printf("El tiempo medio de viaje es: %0.2f\n", avg_travel_time);
			}
			close(fd);
		}
		else if (choice == 5)
		{
			exit(1);
		}
		else
		{
			printf("Entre una opcion adecuada.\n");
		}
	}
}

void Menu()
{
	printf("%s", "\nPor favor seleccione una de las siguientes opciones:\n");
	printf("%s", "1. Ingresar origen\n2. Ingresar destino\n");
	printf("%s", "3. Ingresar hora\n4. Buscar tiempo de viaje medio\n");
	printf("%s", "5. Salir\n\n");
}
