#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in myaddr;
    struct sockaddr_in clientaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(8086);
    int clientaddr_len = sizeof(clientaddr);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
	printf("socket error\n");
	exit(-1);
    }
    if(bind(server_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
	printf("bind error\n");
	exit(-1);
    } 
    if(listen(server_fd, 10) == -1)
    {
	printf("listen error\n");
	exit(-1);
    }
    printf("listenning......\n");
    while(1)
    {

	client_fd = accept(server_fd, (struct sockaddr *)&clientaddr, &clientaddr_len);
	    if(client_fd == -1)
   	 {
		printf("accept error\n");
		exit(-1);
   	 }
   	 char message[4096];
   	 recv(client_fd, message, 100, 0);
   	 printf("receive from client: %s\n", message);
   	 close(client_fd);
    }
    close(server_fd);
    return 0;
}
