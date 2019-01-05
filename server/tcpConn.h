#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <String>

#define SA (struct sockaddr_in)
#define BUFMAXLEN 1024

using namespace std;


class TcpConn {
    public:
        TcpConn(String addr, int port) {
            this.addr = addr;
            this.port = port;
        }

        int createSocket();
        int tcpAccept();
        int tcpRecv(int connFd, int buf[]);
        int tcpSend();
        bool closeListenSocket();
    private : 
        String addr;
        int port;

        int listenFd, connFd;
        int buf[BUFMAXLEN];
}
