#include "server.h"

int main() {
    char buf[4096];
    TcpConn listtenSocket("127.0.0.1", 8086);
    int listenFd = listtenSocket.createSocket();
    cout << "listen port 8086: " << listenFd << endl;

    while(true) {
        int connFd = listtenSocket.tcpAccept(listenFd);
        if(connFd < 0) {
            cout << "accept error" << endl;
        }
        int n;
        n = listtenSocket.tcpRecv(connFd, buf);
        if (n > 0) {
            buf[n] = '\0';
            cout <<  buf << endl;
        }
    }

    return 0;
}
