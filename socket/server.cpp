/*
* main.cpp
*
* By: Cesar
* Created on: Apr. 1st, 2020 
*
*/
#define PORT 8031
#define MAXLINE 1

#include "Socket.h"
#include <string.h>

int main() {

	int sockfd;
	unsigned char buffer[MAXLINE];
	unsigned char starT[] = "I";
	unsigned char *start = starT;
	struct sockaddr_in		servaddr;
	std::string ip_address = "0.0.0.0";

	// Create Socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0 ,sizeof(servaddr));

	//Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	Socket communication(0, PORT, ip_address);
	communication.rcvPacket(buffer);


	return 0;

}