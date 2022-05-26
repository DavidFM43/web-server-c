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


#define PORT 3535
#define BACKLOG 2

/*
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
*/

int serverfd;

int main(){

    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
    int r, l = 0;
    int* data = malloc(sizes[l]);

	struct timeval start, end;

    int clientfd, opt = 1;
    struct sockaddr_in server, client;
    socklen_t tamano;


    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverfd < 0){
        perror("\n error server socket(): ");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero, 8); 

    setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

    r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if(r < 0){
        perror("\n error server bind(): ");
        exit(-1);
    }

    r = listen(serverfd, BACKLOG);
    if(r < 0){
        perror("\n error server listen(): ");
        exit(-1);
    }

    clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
	gettimeofday(&start, NULL); 
    if(clientfd < 0)
    {
        perror("\n error server accept(): ");
        exit(-1);
    }
	for( int i=0; i<sizes[l]/4; i++ ){
        *(data+i) = 420;
    }
    r = send(clientfd, data, sizes[l], 0);
    if(r < 0){
        perror("\n error server send(): ");
        exit(-1);
    }

	gettimeofday(&end, NULL);

	printf("time server: %f\n", (double) ((end.tv_sec - start.tv_sec)*1000000L	+ end.tv_usec - start.tv_usec));

    close(clientfd);
    close(serverfd);
}