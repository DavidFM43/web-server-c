#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Menu();

int main()
{
    char choice;
	int c;
	bool flag = true;

	int origin_id;
	int destination_id;
	int hour;
	float avg_travel_time;

	printf("%s", "Bienvenido\n");

	while (flag) {
        Menu();
        char s[100];
		char buf[128];
        char choice;
        char *p;
        while (fgets(buf, sizeof buf, stdin)) {
            choice = buf[0];
            if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5') {
                if (buf[1] == '\n') break;
                else printf("Introduzca una entrada adecuada.\n");
            }
        }
        switch(choice){
            case '1':
                while (true){
                    printf("Ingrese ID del origen: ");
                    while (fgets(s, sizeof(s), stdin)) {
                        origin_id = strtol(s, &p, 10);
                        if (p == s || *p != '\n') {
                            printf("Inserte una entrada adecuada.\nIngrese ID del origen: ");
                        } else break;
                    }
                    if (origin_id >= 1 && origin_id <= 1160){
                        // search csv file
                        break;
                    }
                    printf("Seleccione un ID entre 1 y 1160.\n");
                }
                break;
            case '2':
                while (true){
                    printf("Ingrese ID de destino: ");
                    while (fgets(s, sizeof(s), stdin)) {
                        destination_id = strtol(s, &p, 10);
                        if (p == s || *p != '\n') {
                            printf("Inserte una entrada adecuada.\nIngrese ID de destino: ");
                        } else break;
                    }
                    if (destination_id >= 1 && destination_id <= 1160){
                        // search csv file
                        break;
                    }
                    printf("Seleccione un ID entre 1 y 1160.\n");
                }
                break;
            case '3':
                while (true){
                    printf("Ingrese hora del dia: ");
                    while (fgets(s, sizeof(s), stdin)) {
                        hour = strtol(s, &p, 10);
                        if (p == s || *p != '\n') {
                            printf("Inserte una entrada adecuada.\nIngrese hora del dia: ");
                        } else break;
                    }
                    if (hour >= 1 && hour <= 23){
                        // search csv file
                        break;
                    }
                    printf("Seleccione una hroa entre 1 y 23.\n");
                }
                break;
            case '4': printf("Solve\n");
                break;
            case '5':
                flag = false;
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
