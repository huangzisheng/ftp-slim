#!/bin/bash
#compile and start server shell
g++ server.cpp tcpConn.cpp -o server
./server
