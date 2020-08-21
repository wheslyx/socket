// Server side implementation of UDP client-server model 
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
  
#define PORT     8080 
#define MAXLINE 1024 
  
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server";
    long long total_packet = 0;
    int temp = 217293; 
    struct sockaddr_in servaddr, cliaddr; 
    unsigned long length;
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
  
    len = sizeof(cliaddr);  //len is value/resuslt 
  
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                (socklen_t*)&len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    //sendto(sockfd, (const char *)hello, strlen(hello),  
    //    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
    //        len);  
    //sendto(sockfd, total_packet, strlen(hello),  
    //    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
    //        (const void*) sizeof(total_packet));
    
    //send(sockfd, &temp, sizeof(temp), MSG_CONFIRM);
    sendto(sockfd, &temp, sizeof(temp),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);

    //sendto(sockfd, total_packet, len, MSG_CONFIRM, (struct sockaddr *) &cliaddr, sizeof(total_packet));

    //printf("Message sent.\n");
    std::cout << "FCS says:" << temp << std::endl;
    std::cout << "1: There is Fatigue" << std::endl; 
    std::cout << "0: No Fatigue" << std::endl;  
      
    return 0; 
} 