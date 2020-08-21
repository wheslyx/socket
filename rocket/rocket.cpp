/*
 * rocket.cpp
 * 
 *  Created on: April 2nd, 2020
 *      Author: Cesar Whesly
 */


#include "rocket.h"


using namespace std;

rocket::rocket(int mode,int port,std::string ip):_ip(ip) {
    
    _sock=socket(AF_INET,SOCK_DGRAM,0);
    printf("socket %d %d %d \n",_sock,mode,port);
    std::cout << "0: Only Read " << std::endl;
    std::cout << "1: Only Send " << std::endl;
    std::cout << "2: Read & Send" << std::endl;
    
    if (mode == ConfigRead) {

        _portListen=port;
        rkt_bind(); // Configuration for server

    }else if(mode == ConfigSend) {

        _portSend=port;
        rkt_portSend(); // Configuration for client

    }else if(mode==ConfigReadSend){

        _portListen=port; // Multiconfiguration Send and Listen
        _portSend=port+10;
        rkt_bind(); 
        rkt_portSend();
    }

    if(_sock<0){

        perror("socket creation failed"); // socket initialization failed
        exit(EXIT_FAILURE);
    }
}

rocket::~rocket(){}

int rocket::rkt_bind(){ // bind IP, PORT and Protocol into a socket

    bzero((char *) &_addr, sizeof(_addr)); // Server address 
    _addr.sin_family = AF_INET; // IPV4 Protocol
    _addr.sin_port=htons(_portListen); // Set port
    _addr.sin_addr.s_addr = htonl(INADDR_ANY); // Set IP
    printf("Server initialization in port %d \n",_portListen);

    int reuse = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        
        perror("Unable to use socket");
        exit(EXIT_FAILURE);

    }

    int status = bind(_sock, (struct sockaddr*) &_addr, sizeof(_addr));
    if (status < 0) {

        std::cout << "Bind Error" << std::endl;
        exit(EXIT_FAILURE);
        return false;

    }

    return true;

}

int rocket::rkt_write(float metric) {
    int len = sizeof(float);
    if(sendto(_sock, &metric, len, 0, (struct sockaddr *)&_client, sizeof(_client))!=len){ // Packet is encapsulated in the variable metric
        cout << "Packet send error!" << endl;
        return false;
    }else{
        return true;
    }
}

int rocket::rkt_writelong(unsigned long long *buf, unsigned long len) {
    if(sendto(_sock, buf, len, 0, (struct sockaddr *)&_client, sizeof(_client))!=len){
        cout << "Error no envio del paquete!" << endl;
        return false;
    }else{
        return true;
    }
}

int rocket::rkt_writeChar(unsigned char *buf, unsigned int len) {
    if(sendto(_sock, buf, len, 0, (struct sockaddr *)&_client, sizeof(_client))!=len){
        cout << "Error no envio del paquete!" << endl;
        return false;
    }else{
    	
        return true;
    }
}

int rocket::rkt_packetChar(unsigned char* data){
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
        
        return received;
    }
}

int rocket::rkt_packet(float metric){ // Communication of float variables, check "Endianness"
    int received=0;
    int addrLength = sizeof(struct sockaddr);
    int len = sizeof(float);
    received = recvfrom(_sock,&metric,len,MSG_WAITALL,(sockaddr *)&_client,(socklen_t*)&addrLength); // reception is stored in "metric"
    if( received < 0) {
        cout << "Packet Recepcion error! "<<std::endl;
        printf(" Value of errno: %d\n ", errno);
        return 0; // returns 0 for error

    }else{

        return received; // successful reception
    }
}

int rocket::rkt_packetlong(unsigned long long* data){
    int received=0;
    int addrLength = sizeof(struct sockaddr);
    received = recvfrom(_sock,data,4096,MSG_WAITALL,(sockaddr *)&_client,(socklen_t*)&addrLength);
    if( received < 0) {
        cout << "Error de recepción del paquete! "<<std::endl;
        printf(" Value of errno: %d\n ", errno);
        perror("Message from perror");
        return 0;

    }else{

        return received;
    }
}

int rocket::rkt_portSend(){
    bzero((char *) &_client, sizeof(_client));
    _client.sin_family=AF_INET;
    _client.sin_port=htons(_portSend);
    _client.sin_addr.s_addr=INADDR_ANY; // makes broadcast
    //int t=inet_aton(_ip.c_str(), &_client.sin_addr);
    return 0; // successful loading IP, Protocol and port parameters
};


void rocket::rkt_finalize() {
    close(_sock);
}