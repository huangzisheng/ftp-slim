#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
	printf("argument count error\n");
	exit(-1);
    }
    int server_fd;
    struct hostent *myhost;
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myhost = gethostbyname(argv[1]);
    if(!myhost)
    {
	printf("get host error");
	exit(-1);
    }
    myaddr.sin_addr = *((struct in_addr *)myhost->h_addr);
    myaddr.sin_port = htons(8086);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
	printf("socket error\n");
	exit(-1);
    }
    if(connect(server_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
	printf("connect error");
	exit(-1);
    }
    printf("Connect with server succeed!!!\n");
    send(server_fd, "hello ftp!", 10, 0);
    close(server_fd);
}
