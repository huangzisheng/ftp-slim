#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <String>

using namespace std;

class TcpConn {
    public:
        TcpConn(String addr, int port) {
            this.addr = addr;
            this.port = port;
        }

        int createSocket();
    private : 
        String addr;
        int port;
        
}
