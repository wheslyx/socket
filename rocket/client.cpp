#include "rocket.h"
#define PORT 8031
#define MAXLINE 18 
int main() {
	
	std::string ip = "0.0.0.0";
	float response;
	float startf= 1000000.f;

	unsigned long long data;

	unsigned char starT[MAXLINE] = "THE END";
	unsigned char *start = starT;
	
	
	rocket communication(1, (int) PORT, ip);
	communication.rkt_write(startf);
	printf("OK \n");
	communication.rkt_packetlong(&data);
	std::cout << "received " << data << std::endl;

	communication.rkt_writeChar(start, (int) MAXLINE);
	std::cout << "Confirmation Sent" << std::endl;

	communication.rkt_finalize();

}