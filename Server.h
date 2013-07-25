/* 
 * File:   Server.h
 * Author: atghosh
 *
 * Created on 19 July, 2013, 12:22 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include "Helper.h"
#include "Socket.h"
#include <map>
#include <time.h>

class Server {
public:
    Server(int port);

    Server() {
    };
    virtual ~Server();
    void start_listening();
    Socket s;
    time_t rawtime;

private:

    static void * wait_stdin(void *arg);
    static void * process_request(void *arg);
    pthread_t stdin_thread;
    pthread_t process_thread;
    static std::map<int, std::pair<std::string, std::string> > client_details;

};
#endif	/* SERVER_H */
