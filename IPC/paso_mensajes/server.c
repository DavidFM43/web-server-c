#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#define PORT 3535
#define BACKLOG 2

int serverfd;

int main(int argc, char *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Incorrect number of arguments supplied.\n");
        exit(-1);
    }

    int r = 0;
    int kbs = atoi(argv[1]);
    int size = 1024 * kbs;
    int *data = malloc(size);

    int clientfd, opt = 1;
    struct sockaddr_in server, client;
    socklen_t tamaño;

    clock_t begin = clock();
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
    {
        perror("Error server socket().\n");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero, 8);

    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(int));

    r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (r < 0)
    {
        perror("Error server bind().\n");
        exit(-1);
    }

    r = listen(serverfd, BACKLOG);
    if (r < 0)
    {
        perror("Error server listen().\n");
        exit(-1);
    }

    clientfd = accept(serverfd, (struct sockaddr *)&client, &tamaño);
    if (clientfd < 0)
    {
        perror("Error server accept().\n");
        exit(-1);
    }
    for (int i = 0; i < size / 4; i++)
    {
        *(data + i) = 420;
    }

    r = send(clientfd, data, size, 0);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // tiempo de escritura

    if (r < 0)
    {
        perror("Error server send().\n");
        exit(-1);
    }

    printf("server time: %f segs.\n", time_spent);

    close(clientfd);
    close(serverfd);
}

char *GenerateSpaceMemory(int kbNum)
{

    int bytes = 1024 * kbNum;
    char *data = malloc(bytes);
    // Filling with a's
    for (int i = 0; i < bytes; i++)
    {
        data[i] = 'a';
    }
    // filling verification
    for (int i = 0; i < bytes; i++)
    {
        if (data[i] != 'a')
        {
            printf("It is not complete");
        }
    }
    return data;
}