/*
* main.cpp
*
* By: Cesar
* Created on: Apr. 1st, 2020
*
*/

#include <iostream>

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

#define PORT 8031
using namespace std;
int main() {

	int _sock, n;
	float response,fatiga = 199.23; //This is hello from client
	struct sockaddr_in _client;
	int len = sizeof(float);
	int _portSend=PORT;
	// Create Socket file descriptor
	if ( (_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	

	
	
	bzero((char *) &_client, sizeof(_client));
    _client.sin_family=AF_INET;
    _client.sin_addr.s_addr=INADDR_ANY;
    _client.sin_port=htons(_portSend);
    

    if(sendto(_sock, &fatiga, len, 0, (struct sockaddr *)&_client, sizeof(_client))!=len){
        std::cout << "Error no envio del paquete!" << std::endl;
      
    }else{
        std::cout << "OK se envio el paquete!" << std::endl;
    }

    int received = 0;
    int addrLength = sizeof(struct sockaddr);
    received = recvfrom(_sock, &response,len,MSG_WAITALL,(sockaddr *)&_client, (socklen_t*)&addrLength);
    if( received < 0) {
        cout << "Error de recepción del paquete! " << received << " - " <<_portSend<<std::endl;
        printf(" Value of errno: %d\n ", errno);
        perror("Message from perror");
    }
    printf("%f \n", response);
	return 0;
}