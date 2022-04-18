#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
void Menu();

int main(){
	bool flag = true;

    // ride variables
	int origin_id;
	int destination_id;
	int hour;
	float avg_travel_time;
    // pipes variables
	int arrSend[3] = {-2,-2,-2}; // -2 means no data
	int fd;

	if (mkfifo("myfifo", 0777) == -1){  // creating fifo file 
		if (errno != EEXIST){
			printf("Could not create fifo file\n");
			return 1;
		}
	}

	printf("%s", "Bienvenido\n");

	while (flag){
        
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
            } else printf("Introduzca una entrada adecuada.\n");
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
						arrSend[0] = origin_id; // saving origin_id for then send
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
						arrSend[1] = destination_id; // saving destination_id for then send
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
                    if (hour >= 0 && hour <= 23){
						arrSend[2] = hour; // saving hour for then send
                        break;
                    }
                    printf("Seleccione una hroa entre 0 y 23.\n");
                }
                break;
            case '4':
                if (arrSend[0] == -2 || arrSend[1] == -2 || arrSend[2] == -2) { // incomplete data
                    printf("Por favor ingrese todos los datos de nuevo.");
                    continue;
                }
				fd = open("myfifo", O_WRONLY); // open pipe for writing
				if (fd == -1){
					return 1; // can't open pipe
				}

				if (write(fd, &arrSend, sizeof(arrSend)) == -1){ 
					return 2; // can't write from pipe
				}

				close(fd);

				fd = open("myfifo", O_RDONLY); // open pipe for reading
				if (fd == -1){
					return 1; // can't open pipe
				}
				if (read(fd, &avg_travel_time, sizeof(float)) == -1){ 
					return 2; // can't read from pipe
				} else {
					if(avg_travel_time == -1.00){
						printf(" NA ");
					} else {
						printf("El tiempo medio de viaje es: %0.2f\n", avg_travel_time);
					}
				}
				close(fd);
                arrSend[0]=-2;
                arrSend[1]=-2;
                arrSend[2]=-2;
                break;
            case '5':
                // sending -1 to close the program
                arrSend[0] = -1;
                arrSend[1] = -1;
                arrSend[2] = -1; 
				fd = open("myfifo", O_WRONLY); // open pipe for writing
				if (fd == -1){
					return 1; // can't open pipe
				}

				if (write(fd, &arrSend, sizeof(arrSend)) == -1){ 
					return 2; // can't write from pipe
				}

				close(fd);

                flag = false;
                break;
        }
	}
	return 0;
}

void Menu(){
	printf("%s", "\nPor favor seleccione una de las siguientes opciones:\n");
	printf("%s", "1. Ingresar origen\n2. Ingresar destino\n");
	printf("%s", "3. Ingresar hora\n4. Buscar tiempo de viaje medio\n");
	printf("%s", "5. Salir\n\n");
}
