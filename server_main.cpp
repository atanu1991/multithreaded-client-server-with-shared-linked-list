/* 
 * File:   client_main.cpp
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:47 PM
 */

#include "Server.h"
#include <signal.h>

void sigintHandler(int signum) {

    ABORT = 1;
    std::map<int, std::pair<std::string, std::string> >::iterator iter = client_details.begin();
    for (iter = client_details.begin(); iter != client_details.end(); ++iter) {
        Helper::writeline(iter->first, (char *) death_msg, sizeof death_msg);
    }
    ::close(serv_port);
    
    intlist.printList(INT_FILE_PATH);
    floatlist.printList(FLOAT_FILE_PATH);
    stringlist.printList(STRING_FILE_PATH);
    
    exit(0);
}

int main(int argc, char *argv[]) {
    short int port; /*port number */
    char *endptr; /*for strtol() */

    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sigintHandler);
    //Check the number of parameters
    if (argc != 2) {
        // Tell the user how to run the program
        // Exactly 2 arguments expected: the program name, the port number the port number to start the server on
        std::cerr << "Usage: " << argv[0] << " <PORT NUMBER>" << std::endl;
        return 1;
    }
    if (argc == 2) {
        port = strtol(argv[1], &endptr, 0);
        if (*endptr) {
            printf("SERVER :Invalid port Number\n");
            exit(EXIT_FAILURE);
        }
    }

    Server sv(port);
    sv.populate_lists();
    sv.start_listening();

    return 0;
}
