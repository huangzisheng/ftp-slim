#include "tcpConn.h"

int TcpConn::createSocket() {
    int listenFd;
    struct sockaddr_in srvAddr;
    
    if (listenFd = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        cerr << "socket error!" << endl;
    }
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (port <= 1024) {
        cerr << "port must greater than 1024" << endl;
        return;
    }
    srvAddr.sin_port = htonl(port);

    if (bind(listenFd, (SA *) &srvAddr, sizeof(srvAddr)) < 0) {
        cerr << "bind error" << endl;
    }

    if (listen(listenFd, LISTENQ) < 0) {
        cerr << "listen error" << endl;
    }

    return listenFd;
}

int TcpConn::tcpAccept() {
    int connFd;
    socklen_t cliLen;
    struct sockaddr_in cliAddr;

    cliLen = sizeof(cliAddr);
    if(connFd = accept(listenFd, (SA *) &cliAddr, cliLen) < 0) {
        cerr << "socket accept error" << end;
    }
    return connFd;
}

bool TcpConn::closeListenSocket(listenFd) {
    if(close(listenFd) < 0) {
        cerr << "close listen error" << endl;
        return false;
    }
    return true;
}

int TcpConn::tcpRecv(int connFd, int buf[]) {
    int recvRet;
    if (recvRet = recv(connFd, buf, BUFMAXLEN, 0) < 0) {
        cerr << "recv error" << endl;
        return -1;
    }
    return recvRet;
}

int TcpConn::tcpSend(int connFd, int buf[]) {
    int sendRet;
    if (sendRet = send(connFd, buf, BUFMAXLEN, 0) < 0) {
        cerr << "send error" << endl;
        return -1;
    }
    return sendRet;
}
