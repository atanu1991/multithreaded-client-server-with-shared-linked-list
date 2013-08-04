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

std::map<int, std::pair<std::string, std::string> > client_details;
LinkedList<std::string> stringlist;
LinkedList<int> intlist;
LinkedList<float> floatlist;

Server::Server(int port) {

    printf("Starting the Server With Port(%d)\n", port);
    /*create a listening socket*/
    s.create();
    /*Bind our socket address to the listening socket*/
    s.bind(port);
}

Server::~Server() {
}

void Server::insert_operation(struct parsed_vals * parm) {
    switch (parm->type) {
        case INT_TYPE:
            intlist.addNode((parm->data).int_data);
            break;
        case FLOAT_TYPE:
            floatlist.addNode((parm->data).float_data);
            break;
        case STRING_TYPE:
            stringlist.addNode((parm->data).str_data);
            break;
    }
}

/*Retrieve an input Line from the connected socket then simply write it back to the same socket*/
void * process_request(void *parm) {
    int tmp = *((int *) parm);
    free(parm);
    pthread_detach(pthread_self());
    int clientsocket = tmp;
    char buffer[MAXLINE];
    while (1) {
        if (Helper::readline(clientsocket, buffer, MAXLINE - 1) < 0) {
            break;
        }
        printf("\nClient with socket id %d Said:  %s\n", clientsocket, buffer);
        if (strncmp(buffer, "exit", 4) == 0) {
            Helper::writeline(clientsocket, buffer, strlen(buffer));
            break;
        }
        struct parsed_vals tokens;
        YY_BUFFER_STATE bp = yy_scan_string(buffer);
        yy_switch_to_buffer(bp);
        int ret_val = yyparse((void *) &tokens);
        if (ret_val == 0) {
            switch (tokens.cmd) {
                case INSERT_CMD:
                    Server::insert_operation(&tokens);
                    break;
                case FIND_CMD:
                    //
                    break;
                case DELETE_CMD:
                    break;
                case DELALL_CMD:
                    break;
                case SHOW_CMD:
                    printf("%d integers\n%d strings\n%d floats\n", intlist.size, stringlist.size, floatlist.size);
                    break;
            }
            //stringlist.addNode(tokens.data.str_data);
        }
        yy_delete_buffer(bp);

        if (Helper::writeline(clientsocket, buffer, strlen(buffer)) < 0) {
            break;
        }
        printf("\nServer Echoed:  %s\n", buffer);
        memset(buffer, 0, sizeof buffer);
    }
    client_details.erase(clientsocket);
    //stringlist.printList();
    if (close(clientsocket) < 0) {
        throw SocketException("Error in calling close");
    }
    pthread_exit(NULL);
}

void* wait_stdin(void *arg) {
    pthread_detach(pthread_self());
    std::string text;
    while (1) {
        std::getline(std::cin, text);
        if (0 == text.compare("show client details")) {

            std::map<int, std::pair<std::string, std::string> >::iterator iter = client_details.begin();

            for (iter = client_details.begin(); iter != client_details.end(); ++iter)
                std::cout << (iter->second).first << ":" << (iter->second).second << '\n';

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

        client_details.insert(std::make_pair(*conn_s, std::make_pair(cli_name, time_accept)));

        if ((pthread_create(&process_thread, NULL, &process_request, conn_s)) != 0) {
            std::cerr << ("SERVER:Error Creating A thread for Socket(%d)\n",
                    *conn_s);
            exit(EXIT_FAILURE);
        }
    }

}
