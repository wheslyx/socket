/*
 * Socket.cpp
 * 
 *  Created on: Feb 7, 2020
 *      Author: alexsantos
 */


#include "Socket.h"
#include <errno.h>

using namespace std;

Socket::Socket():_sock(-1) {}
Socket::Socket(int mode,int port,string ip):_sock(-1),_ip(ip) {
    //memset(&_addr,0,sizeof _addr);
	_sock=socket(AF_INET,SOCK_DGRAM,0);
    //_sock = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket %d %d %d \n",_sock,mode,port);
    if(mode==CfgOnlyRead) {_portListen=port;bind();}
    else if(mode==CfgOnlySend) {_portSend=port;loadPortSend();
        printf("hola");}
    else if(mode==CfgReadSend){
           _portListen=port;
           _portSend=port+10;
           bind();loadPortSend();
    }

    if(_sock<0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
}

Socket::~Socket(){}

int Socket::bind(){

    bzero((char *) &_addr, sizeof(_addr));
    //memset(&addr, 0, sizeof(addr));
    _addr.sin_family = AF_INET;
    //_addr.sin_addr.s_addr = inet_addr(ip);;
    _addr.sin_port=htons(_portListen);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_aton(ip , &_addr.sin_addr.s_addr);
    printf("Servidor iniciado en el puerto: %d \n",_portListen);

    int reuse = 1;
    //(char*)
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("no es posible reusar el socket");
        exit(EXIT_FAILURE);
    }

    int status = ::bind(_sock, (struct sockaddr*) &_addr, sizeof(_addr));
    if (status < 0) {
        //throw AppException(TAG, __LINE__, "ERROR on binding");
        cout << "Error no bind" << std::endl;
        return false;
    }

    return true;
}

int Socket::socket_write(unsigned long long *buf, unsigned long len) {
    if(sendto(_sock, buf, len, 0, (struct sockaddr *)&_client, sizeof(_client))!=len){
        cout << "Error no envio del paquete!" << endl;
        return false;
    }else{
        return true;
    }
}

int Socket::socket_writeChar(unsigned char *buf, unsigned int len) {
    if(sendto(_sock, buf, len, 0, (struct sockaddr *)&_client, sizeof(_client))!=len){
        cout << "Error no envio del paquete!" << endl;
        return false;
    }else{
    	/*printf("Data no sale,%d ",len);
    	for(int i=0;i<len;i++){
    		printf("%02X",buf[i]);
    	}
    	printf("\n");*/
        return true;
    }
}

int Socket::rcvPacket(unsigned char* data){
    int received=0;
    //char data[256];
    int addrLength = sizeof(struct sockaddr);
    //printf("sizeof data %d \n",sizeof(data));
    received = recvfrom(_sock,data,4096,MSG_WAITALL,(sockaddr *)&_client,(socklen_t*)&addrLength);
    if( received < 0) {
        cout << "Error de recepción del paquete!" << std::endl;
        printf(" Value of errno: %d\n ", errno);
        perror("Message from perror");
        return 0;
    }else{
        //int length=sizeof(data);
        // std::string ss = data;
        //std::string ss;
        //memcpy(&ss, data,sizeof(data));
        //cout<<data[0] <<endl;
        //printf("datos %02X ",data[8]);
        //printf(" Dirección IP: %s \n", inet_ntoa(_client.sin_addr));
        return received;
    }
}

int Socket::rcvPacketLL(unsigned long long* data){
    int received=0;
    //char data[256];
    int addrLength = sizeof(struct sockaddr);
    //printf("sizeof data %d \n",sizeof(data));
    received = recvfrom(_sock,data,4096,MSG_WAITALL,(sockaddr *)&_client,(socklen_t*)&addrLength);
    if( received < 0) {
        cout << "Error de recepción del paquete! " << received << " - " <<_portListen<<std::endl;
        printf(" Value of errno: %d\n ", errno);
        perror("Message from perror");
        return 0;
    }else{
        //int length=sizeof(data);
        // std::string ss = data;
        //std::string ss;
        //memcpy(&ss, data,sizeof(data));
        //cout<<data[0] <<endl;
        //printf("datos %02X ",data[8]);
        //printf(" Dirección IP: %s \n", inet_ntoa(_client.sin_addr));
        return received;
    }
}

int Socket::loadPortSend(){
    bzero((char *) &_client, sizeof(_client));
    _client.sin_family=AF_INET;
    //_client.sin_addr.s_addr=inet_addr("127.0.0.1"); 
    _client.sin_port=htons(_portSend);
    int t=inet_aton(_ip.c_str(), &_client.sin_addr);
    return 0;
};


 

void Socket::finalize() {
    close(_sock);
}

