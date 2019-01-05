#include "server.h"

int main() {
    TcpConn listtenSocket("127.0.0.1", 8086);
    int listenFd = listtenSocket.createSocket();
    cout << "listen port 8086" << endl;

    //while(true) {
        int connFd = listtenSocket.tcpAccept(listenFd);
        cout << "connFd: " << connFd << endl;
    //}

    return 0;
}
