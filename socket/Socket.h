/*
 * Socket.h
 *
 *  Created on: Feb 7, 2020
 *      Author: alexsantos
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#define CfgOnlyRead 0
#define CfgOnlySend 1
#define CfgReadSend 2

#include <netinet/in.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>

class Socket {
public:
    Socket();
    Socket(int mode,int port,std::string ip="127.0.0.1");
    ~Socket();
    int bind();
    int socket_write(unsigned long long* buf, unsigned long len);
    int socket_writeChar(unsigned char* buf, unsigned int len);
    void socket_received(unsigned char*);
    void finalize();
    int rcvPacket(unsigned char* data);
    int rcvPacketLL(unsigned long long* data);
    int loadPortSend();
private:
    int _portListen,_portSend, _sock;
    std::string _ip;
    struct sockaddr_in _addr;
    struct sockaddr_in _client;
};



#endif /* SOCKET_H_ */
