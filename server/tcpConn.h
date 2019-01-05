#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
using namespace std;

#define BUFMAXLEN 4096

using namespace std;


class TcpConn {
    public:
        TcpConn(string addr, int port) {
            this->addr = addr;
            this->port = port;
        }

        int createSocket();
        int tcpAccept(int listenFd);
        int tcpRecv(int connFd, char buf[]);
        int tcpSend(int connFd, char buf[]);
        bool closeListenSocket(int listenFd);
    private : 
        string addr;
        int port;

        int listenFd, connFd;
        char buf[BUFMAXLEN];
};
