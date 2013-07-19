/* 
 * File:   client_main.cpp
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:47 PM
 */

#include "Server.h"
#include <signal.h>

int main(int argc, char *argv[]) {
    short int port; /*port number */
    char *endptr; /*for strtol() */

    signal(SIGPIPE, SIG_IGN);

    //signal(SIGINT, SIG_IGN);
    // Check the number of parameters
    if (argc != 2) {
        // Tell the user how to run the program
        // Exactly 2 arguments expected: the program name, the port number the port number to start the server on
        std::cerr << "Usage: " << argv[0] << " <PORT NUMBER>" << std::endl;
        return 1;
    }
    if (argc == 2) {
        port = strtol(argv[1], &endptr, 0);
        if (*endptr) {
            printf("ECHOSERV :Invalid port Number\n");
            exit(EXIT_FAILURE);
        }
    }

    Server sv(port);
    sv.start_listening();

    return 0;
}
