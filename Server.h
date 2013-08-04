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
#include "Globals.h"
#include "LinkedList.cpp"
#include "Globals.h"
#include "Lexheader.h"
#include "yacc_file.tab.hh"
#include <map>
#include <time.h>

extern LinkedList<std::string> stringlist;
extern LinkedList<int> intlist;
extern LinkedList<float> floatlist;
extern std::map<int, std::pair<std::string, std::string> > client_details;

void * wait_stdin(void *arg);
void * process_request(void *arg);
int yyparse(void *);

class Server {
public:
    Server(int port);

    Server() {
    };
    virtual ~Server();
    void start_listening();
    Socket s;
    time_t rawtime;
    static void insert_operation(struct parsed_vals *);
private:

    pthread_t stdin_thread;
    pthread_t process_thread;

};
#endif	/* SERVER_H */
