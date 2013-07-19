/* 
 * File:   Server.cpp
 * Author: atghosh
 * 
 * Created on 19 July, 2013, 12:36 PM
 */

#include "Server.h"
#include "Socket.h"
#include "SocketException.h"
#include <map>

Server::Server(int port) {

    printf("Starting the Server With Port(%d)\n", port);
    /*create a listening socket*/
    s.create();
    /*Bind our socket address to the listening socket*/
    s.bind(port);
}

Server::~Server() {
}

std::multimap<std::string, std::string> Server::client_details;

/*Retrieve an input Line from the connected socket then simply write it back to the same socket*/
void * Server::process_request(void *parm) {
    int tmp = *((int *) parm);
    free(parm);
    pthread_detach(pthread_self());
    int clientsocket = tmp;
    char buffer[MAXLINE];
    do {
        if (Helper::readline(clientsocket, buffer, MAXLINE - 1) < 0) {
            break;
        }
        printf("\nClient with socket id %d Said:  %s\n", clientsocket, buffer);
        //Parse here --- Have to learn parsing :(
        if (Helper::writeline(clientsocket, buffer, strlen(buffer)) < 0) {
            break;
        }
        printf("\nServer Echoed:  %s\n", buffer);
    } while (strncmp(buffer, "BYE", 3));
    if (close(clientsocket) < 0) {
        throw SocketException("Error in calling close");
    }
    pthread_exit(NULL);
}

void* Server::wait_stdin(void *arg) {

    pthread_detach(pthread_self());
    std::string text;
    while (1) {
        std::getline(std::cin, text);
        if (0 == text.compare("show client details")) {
            std::multimap<std::string, std::string>::iterator iter = client_details.begin();

            for (iter = Server::client_details.begin(); iter != Server::client_details.end(); ++iter)
                std::cout << iter->first << ":" << iter->second << '\n';

        }

    }
    pthread_exit(NULL);

}

void Server::start_listening() {

    s.listen();
    if ((pthread_create(&stdin_thread, NULL, &wait_stdin, NULL)) != 0) {
        std::cerr << ("SERVER:Error Creating A thread for stdin\n");
        exit(EXIT_FAILURE);
    }
    std::string cli_name;
    while (1) {

        int *conn_s;
        std::string time_accept;
        conn_s = (int *) malloc(sizeof (int));
        cli_name = s.accept(conn_s);

        //Insert into static map to keep track of all clients
        time(&rawtime);
        time_accept = ctime(&rawtime);

        client_details.insert(std::pair<std::string, std::string>(cli_name, time_accept));

        if ((pthread_create(&process_thread, NULL, &process_request, conn_s)) != 0) {
            std::cerr << ("SERVER:Error Creating A thread for Socket(%d)\n",
                    *conn_s);
            exit(EXIT_FAILURE);
        }
    }

}