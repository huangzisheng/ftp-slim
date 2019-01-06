#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

int client_fd;
void response(char *request);
void receiveFile(int client_fd);

int main()
{
    int server_fd;
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
   	 char conntype[10];
   	 recv(client_fd, conntype, 10, 0);
	 conntype[strlen(conntype)] = '\0';
	 response(conntype);
   	 close(client_fd);
    }
    close(server_fd);
    return 0;
}

void response(char * request)
{
    if(request[0] == '1')
    {
	receiveFile(client_fd);	
    }
}

void receiveFile(int client_fd)
{
    //char filename[1024];
    //if(recv(client_fd, filename, sizeof(filename), 0) == -1)
    //{
	//printf("Receive file name failed!\n");
	//return;
    //}
    //printf("receive from client. filename: %s\n", filename);
    
    //int len = strlen(filename);
    //filename[len] = '2';
    //filename[len+1] = '\0';
    int file_fd = creat("receivefile", 0777);
    if(file_fd == -1)
    {
	printf("Create file failed!\n");
	return;
    }    
    char buf[4096];
    if(recv(client_fd, buf, sizeof(buf), 0) == -1)
    {
	printf("Receive file failed!\n");
	return;
    }
    //printf("file context: %s\n", buf);
    if(write(file_fd, buf, strlen(buf)) == -1)
    {
	printf("Write to copy file failed!\n");
	return;
    }
    printf("Receive file successful!\n");
    if(close(file_fd) == -1)
    {
	printf("Close file failed!\n");
	return;
    }
}
