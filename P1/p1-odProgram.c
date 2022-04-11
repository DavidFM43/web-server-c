#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){
	int choice = 0;
	bool running = true;

    int origin_id;
    int destination_id;
    int hour;
    float avg_travel_time;

	printf("%s", "Bienvenido\n\n");

	while(running)
	{

		printf("%s", "Por favor seleccione una de las siguientes opciones:\n");
		printf("%s", "1. Ingresar origen\n2. Ingresar destino\n");
		printf("%s", "3. Ingresar hora\n4. Buscar tiempo de viaje medio\n");
		printf("%s", "5. Salir\n\n");

		// TODO: Account for wrong input type(all scanfs)
		scanf("%d", &choice);

		if(choice == 1){

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
			
		} else if(choice == 2){

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

		} else if(choice == 3){

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

		} else if(choice == 4){

			printf("Tiempo de viaje medio:");
			scanf("%d", &avg_travel_time);
			// search csv file

		} else if(choice == 5) {

            exit(1);

		} else {

            printf("Entre una opcion adecuada.\n\n");

		}

	}
}
