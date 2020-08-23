#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

#define PORT     6790
#define MAXLINE 1024 
  
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE];

    //char *hello = "Hello from client"; 
    std::string hello = "Hello from Control Screen";
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len; 
      
    sendto(sockfd, hello.c_str(), strlen(hello.c_str()), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr));

    //sendto(sockfd, (const char *)hello, strlen(hello), 
    //    MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
    //        sizeof(servaddr)); 
    printf("Control Screen message sent.\n"); 
    std::cout << hello << std::endl;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                (socklen_t*)&len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
    //std::cout << "Receive : " <<  buffer << std::endl ;
    close(sockfd); 
    return 0; 
} 