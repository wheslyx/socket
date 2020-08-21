#include "rocket.h"
#define PORT  8031
#define MAXLINE 18

int main() {
	
	float response = 25.0;
	float start = 1.0; 
	std::string ip = "0.0.0.0";

	long long unsigned data = 221345878677565343;
	unsigned long len = sizeof(unsigned long);

	unsigned char buffer[MAXLINE];

	rocket communication(0, (int) PORT, ip);
	communication.rkt_packet(start);
	std::cout << "Out " << start << std::endl;

	communication.rkt_writelong(&data,len);
	std::cout << "sent " << data << std::endl;

	communication.rkt_packetChar(buffer);
	std::cout << "Confirmation " << buffer << std::endl;

}