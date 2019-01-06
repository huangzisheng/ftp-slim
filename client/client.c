#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

int server_fd;
bool init(char *ip);
void usage();
int function();
void run(int fun);
bool connType(int fun);
bool sendfile(int sockfd);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
	printf("argument count error\n");
	exit(-1);
    }
    if(!init(argv[1]))
    {
	printf("Init error!\n");
	exit(-1);
    }
    usage();
    int sec = function();
    run(sec);
    return 0;
}

bool init(char *ip)
{
    struct hostent *myhost;
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myhost = gethostbyname(ip);
    if(!myhost)
    {
	printf("get host error");
	return false;
	exit(-1);
    }
    myaddr.sin_addr = *((struct in_addr *)myhost->h_addr);
    myaddr.sin_port = htons(8086);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
	printf("socket error\n");
	return false;
	exit(-1);
    }
    if(connect(server_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
	printf("connect error\n");
	return false;
	exit(-1);
    }
    printf("Connect with server succeed!!!\n");
    return true;
}

void usage()
{
    printf("********** Ftp-slim **********\n");
    printf("\n");
    printf("1.send file\n");
    printf("2.quit\n");
    printf("\n");
    printf("******************************\n");
    printf("select the function: ");
}

int function() 
{
    int sec;
    scanf("%d", &sec);
    
    while(sec != 1 && sec != 2)
    {
	printf("Please enter the right number: ");
	scanf("%d", &sec);
    }
    return sec;
}

bool connType(int fun)
{
    char control[10];
    sprintf(control, "%d", fun);
    if(send(server_fd, control, 1, 0) == -1)
    {
	printf("Control error!\n");
	exit(-1);
    }
    return true;
}

void run(int function)
{
    switch(function)
    {
	case 1:
	    if(connType(function))
	    {
	        while(!sendfile(server_fd))
		    ;
	    }
	    break;
	case 2:
	    exit(-1);
	default:
	    return;
    }
}

bool sendfile(int sockfd)
{
    char buff[4096];
    printf("Enter the file name: ");
    scanf("%s", buff);
    int len = strlen(buff);
    char filename[len + 1];
    strcpy(filename, buff);
    filename[strlen(buff)] = '\0';
    int file_fd = open(filename, O_RDONLY);
    if(file_fd == -1)
    {
	printf("open file failed!\n");
	return false;
    }
    //if(send(server_fd, filename, sizeof(filename), 0) == -1)
    //{
	//printf("Send filename failed!\n");
	//exit(-1);
    //}
    
    printf("Sure to send?(Y/n)");
    char confirm;
    scanf("%s", &confirm);
    if(confirm == 'N' || confirm == 'n')
    {
	exit(-1);
    }
    
    if(confirm == 'Y' || confirm == 'y')
    {
    	int length = read(file_fd, buff, sizeof(buff));
    	if(length == -1)
    	{
		printf("read file falied!\n");
		return false;
    	}
    	if(send(server_fd, buff, sizeof(buff), 0) == -1)
    	{
		printf("send file falied!\n");
		return false;
    	}
   	 printf("send file successful!\n");
    	return true;
    }
}
