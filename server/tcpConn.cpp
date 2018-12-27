#include "tcpConn.h"

int TcpConn::createSocket() {
    int listenFd;
    socketlen_t len;
    struct sockaddr_in srvAddr;
    
    if (listenFd = Socket(AF_INET, SOCK_STREAM, 0) < 0) {
        cerr << "socket error!" << endl;
    }
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAddr.sin_port = htonl(port);

    if (Bind(listenFd, (SA *) &srvAddr, sizeof(srvAddr)) < 0) {
        cerr << "bind error" << endl;
    }

    if (Listen(listenFd, LISTENQ) < 0) {
        cerr << "listen error" << endl;
    }

    return listenFd;
}
