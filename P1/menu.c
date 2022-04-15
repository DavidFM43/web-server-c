#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

void Menu();

int main()
{
	int choice = 0;
	int c;

	int origin_id;
	int destination_id;
	int hour;
	float avg_travel_time;

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
					// search csv file
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
					// search csv file
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
					// search csv file
					break;
				}
				printf("Seleccione una hora entre 0 y 23.\n");
			}
		}
		else if (choice == 4)
		{
			float d;
			printf("Tiempo de viaje medio: ");
			scanf("%f", &avg_travel_time);
			// search csv file
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
