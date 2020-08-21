/*
* main.cpp
*
* By: Cesar
* Created on: Apr. 1st, 2020 
*
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <errno.h>
#include <netdb.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#define PORT 8031
using namespace std;
int main() {

	int _sock,n;
	float value;
	float reply = 25.0;
	struct sockaddr_in _addr,_client;
	int len = sizeof(float);
	int _portListen=PORT;
	// Create Socket file descriptor
	if ( (_sock=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	
	bzero((char *) &_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port=htons(_portListen);
    _addr.sin_addr.s_addr = INADDR_ANY;
    printf("Servidor iniciado en el puerto: %d \n",_portListen);

    int reuse = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("no es posible reusar el socket");
        exit(EXIT_FAILURE);
    }

    int status = bind(_sock, (struct sockaddr*) &_addr, sizeof(_addr));
    if (status < 0) {
        cout << "Error no bind" << std::endl;
        exit(EXIT_FAILURE);
    }

    int received=0;
    int addrLength = sizeof(struct sockaddr);
    received = recvfrom(_sock,&value,len,MSG_WAITALL,(sockaddr *)&_client,(socklen_t*)&addrLength);
    if( received < 0) {
        cout << "Error de recepción del paquete! " << received << " - " <<_portListen<<std::endl;
        printf(" Value of errno: %d\n ", errno);
        perror("Message from perror");
    }
    printf("%f \n", value);

    if(sendto(_sock, &reply, len, 0, (struct sockaddr *)&_client,sizeof(_addr))!=len){
        std::cout << "Error no envio del paquete!" << std::endl;
      
    }else{
        std::cout << "OK se envio el paquete!" << std::endl;
    }

    printf("Reply sent");
	return 0;

}