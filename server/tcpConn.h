#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
using namespace std;

#define BUFMAXLEN 1024

using namespace std;


class TcpConn {
    public:
        TcpConn(string addr, int port) {
            this->addr = addr;
            this->port = port;
        }

        int createSocket();
        int tcpAccept(int listenFd);
        int tcpRecv(int connFd, int buf[]);
        int tcpSend(int connFd, int buf[]);
        bool closeListenSocket(int listenFd);
    private : 
        string addr;
        int port;

        int listenFd, connFd;
        int buf[BUFMAXLEN];
};
