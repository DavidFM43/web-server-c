#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 3535


int main(int argc, char *argv[])
{
    int clientfd, r;
    struct sockaddr_in client;
    struct hostent *he;
    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
    int l = 0;
    int* data = malloc(sizes[l]);

	struct timeval start, end;
    
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd < 0){
        perror("\n error en socket(): ");
        exit(-1);
    }
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    inet_aton("127.0.0.1", &client.sin_addr);
    
    r = connect(clientfd, (struct sockaddr *)&client, (socklen_t)sizeof(struct sockaddr));
	gettimeofday(&start, NULL); 
    if(r < 0){
        perror("\n error en connect(): ");
        exit(-1);
    }
    r = recv(clientfd, data, sizes[l], 0);
	if(r < 0){
        perror("\n error en connect(): ");
        exit(-1);
    }
	gettimeofday(&end, NULL);

	printf("time cliente: %f\n", (double) ((end.tv_sec - start.tv_sec)*1000000L	+ end.tv_usec - start.tv_usec));

    close(clientfd);

}