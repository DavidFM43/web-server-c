#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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

	int arrSend[3];
	int fd;

	if(mkfifo("myfifo", 0777) == -1){  //creating fifo file 
		if(errno != EEXIST) {
		 	printf("Could not create fifo file\n");
			return 1;
		}
	}


	printf("%s", "Bienvenido\n");

	while (true)
	{
		Menu();

		fd = open("myfifo", O_WRONLY);
		if (fd == -1){ //depuration
		return 1;

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
					arrSend[0] = origin_id; //saving origin_id for then send
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
					arrSend[1] = destination_id; //saving destination_id for then send
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
					arrSend[2] = hour; //saving hour for then send
					break;
				}
				printf("Seleccione una hora entre 0 y 23.\n");
			}
		}
		else if (choice == 4)
		{	
			if (write(fd, arrSend, sizeof(arrSend)) == -1){ //writting in the FIFO
				return 2; //depuration
			}
			float d;
			printf("Tiempo de viaje medio: ");
			scanf("%f", &avg_travel_time);
			close(fd);
		}
		else if (choice == 5)
		{
			exit(1);
			close(fd); 
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
