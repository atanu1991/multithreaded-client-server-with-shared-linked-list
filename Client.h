/* 
 * File:   Client.h
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:46 PM
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include "Helper.h"
#include "Socket.h"
#include <string>

class Client {
public:
    Client(std::string host, int port);

    Client() {
    };
    virtual ~Client();
    Socket s;
    int socket_id;
    void handle_client(FILE *, int);
private:
    
};

#endif	/* CLIENT_H */

