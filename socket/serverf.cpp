#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv)
{
 float c;
 int listenfd, connfd, n;
 socklen_t clilen;
 char buf[MAXLINE], buf256[256], buffer[256];
 unsigned char len = strlen(buffer);
 struct sockaddr_in cliaddr, servaddr;

 //creation of the socket
 listenfd = socket (AF_INET, SOCK_STREAM, 0);

 //preparation of the socket address 
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERV_PORT);

 bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

 listen(listenfd, LISTENQ);

 printf("%s\n","Server running...waiting for connections.");

 for ( ; ; ) {

  clilen = sizeof(cliaddr);
  connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
  printf("%s\n","Received request...");

  while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
   printf("%s","String received from and resent to the client:");
   puts(buf);


   recv(connfd, &len, sizeof len, 0);
   recv(connfd, buf256, len, 0);
   recv(connfd, buffer, 256, 0);
   buf256[len] = 0;
   sscanf(buffer, "%f", &c);
   puts(buffer);
   printf ("\n%f", &c);   
   send(connfd, buf, n, 0);
  }

 if (n < 0) {
  perror("Read error"); 
  exit(1);
 }
 close(connfd);

 }
 //close listening socket
 close(listenfd); 
}