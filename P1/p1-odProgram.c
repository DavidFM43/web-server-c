#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){

	int choice = 0;
	bool running = true;
	printf("%s", "Bienvenido\n\n");

	while(running)
	{
	
		printf("%s", "Por favor seleccione una de las siguientes opciones:\n");
		printf("%s", "1. Ingresar origen\n");
		printf("%s", "2. Ingresar destino\n");
		printf("%s", "3. Ingresar hora\n");
		printf("%s", "4. Buscar tiempo de viaje medio\n");
		printf("%s", "5. Salir\n");

		// TODO: Account for wrong input type(all scanfs)
		scanf("%d", &choice);

		switch (choice)
		{
		// TODO: Encapsular casos 1 y 2 mediante una función.
		case 1:
		 	int origin_id;

			while(true)	
			{
				printf("Ingrese ID del origen:");
				scanf("%d", &origin_id);	

				if(origin_id >= 1 && origin_id <= 1160){
					// search csv file
					break;
				}

				printf("Seleccione un ID entre 1 y 1160. ");
			}
			break;
		
		case 2:
		 	int destination_id;

			while(true)	
			{
				printf("Ingrese ID del destino:");
				scanf("%d", &destination_id);	

				if(destination_id >= 1 && destination_id <= 1160){
					// search csv file
					break;
				}

				printf("Seleccione un ID entre 1 y 1160. ");
			}
			break;

		case 3:
		 	int hour;

			while(true)	
			{
				printf("Ingrese hora del día:");
				scanf("%d", &hour);	

				if(hour >= 0 && hour <= 23){
					// search csv file
					break;
				}

				printf("Seleccione una hora entre 0 y 23. ");
			}
			break;

		case 4:
		 	float avg_travel_time;

			printf("Tiempo de viaje medio:");
			scanf("%d", &avg_travel_time);	
			// search csv file
			break;

		case 5:
		 	exit(1);
			break;

		default: // invalid option
		 	printf("Por favor ingrese una opción adecuada.\n\n");
			break;
		}

	}
}
