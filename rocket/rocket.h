/*
 * rocket.h
 *
 *  Created on: April 2nd, 2020
 *      Author: Cesar Whesly
 */

#ifndef ROCKET_H_
#define ROCKET_H_

#define ConfigRead 0
#define ConfigSend 1
#define ConfigReadSend 2

#include <netinet/in.h>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>


class rocket {
public:
    /**
         * @brief      Initialize class rocket
         *
         * @param      configuration mode, 
         *
         * @return     object or call to class
    */

    rocket(int mode,int port,std::string ip="127.0.0.1");
    
    /**
         * @brief      class rocket destructor
         *
         * @param      none 
         *
         * @return     releases program memory 
    */
    ~rocket();

    /**
         * @brief      Defines socket port, protocol, IP version and if it is reusable
         *
         * @param      none
         *
         * @return     True for success, False for failure
    */
    int rkt_bind(); 

    /**
         * @brief      Sends/TX float data type over socket
         *
         * @param      float data
         *
         * @return     True for success, False for failure
    */
    
    int rkt_write(float buf);

    /**
         * @brief      Sends/TX long data type over socket
         *
         * @param      long long data
         *
         * @return     True for success, False for failure
    */

    int rkt_writelong(unsigned long long* buf, unsigned long len);

    /**
         * @brief      Sends/TX Character data type over socket
         *
         * @param      characters
         *
         * @return     True for success, False for failure
    */

    int rkt_writeChar(unsigned char* buf, unsigned int len);

    /**
         * @brief      Receive/RX float data type over socket
         *
         * @param      float data
         *
         * @return     Higher than "0" for success and "0" for failure
    */

    int rkt_packet(float data);

    /**
         * @brief      Receive/RX character data type over socket
         *
         * @param      characters
         *
         * @return     Higher than "0" for success and "0" for failure
    */

    int rkt_packetChar(unsigned char* data);

    /**
         * @brief      Receive/RX long data type over socket
         *
         * @param      long long data
         *
         * @return     Higher than "0" for success and "0" for failure
    */

    int rkt_packetlong(unsigned long long* data);

    /**
         * @brief      Sets up configuration for client socket: IPV4, port to write and address.
         *
         * @param      none
         *
         * @return     "0" for success
    */
    int rkt_portSend();

     /**
         * @brief      Close Socket
         *
         * @param      none
         *
         * @return     none
    */
    void rkt_finalize();
private:

    int _portListen,_portSend, _sock; // Socket and port for server: _portListen,  port for client _PortSend
    std::string _ip; // IP address of server
    struct sockaddr_in _addr; // server socket structure
    struct sockaddr_in _client; // cliente socket structure
};



#endif /* SOCKET_H_ */
