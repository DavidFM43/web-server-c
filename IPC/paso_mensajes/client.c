#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#define PORT 3535

int main(int argc, char *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Incorrect number of arguments supplied.\n");
        exit(-1);
    }

    int clientfd, r;
    struct sockaddr_in client;

    int kbs = atoi(argv[1]);
    int size = 1024 * kbs;
    int *data = malloc(size);

    clock_t begin = clock();
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        perror("Error en socket().\n");
        exit(-1);
    }
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    inet_aton("127.0.0.1", &client.sin_addr);

    r = connect(clientfd, (struct sockaddr *)&client, (socklen_t)sizeof(struct sockaddr));
    if (r < 0)
    {
        perror("Error en connect().\n");
        exit(-1);
    }
    r = recv(clientfd, data, size, 0);
    if (r < 0)
    {
        perror("Error en connect().\n");
        exit(-1);
    }

    close(clientfd);

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // tiempo de escritura
    printf("client time: %f segs.\n", time_spent);
}