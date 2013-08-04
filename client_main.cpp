/* 
 * File:   client_main.cpp
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:47 PM
 */
#include "Client.h"
#include "Socket.h"
#include <string>

int main(int argc, char* argv[]) {
    int port;
    char *endptr; //for strtol()
    char *svraddr = (char *) SERV_HOST_ADDR;
    if (argc == 2 || argc == 3) {
        port = strtol(argv[1], &endptr, 0);
        if (*endptr) {
            std::cerr << ("CLIENT:Invalid Port Number\n");
            exit(1);
        }
        if (argc == 3) {
            svraddr = argv[2];
        }
    } else if (argc > 3 || argc <= 1) {
        printf("\nCLIENT:Invalid Number Of Command Line Arguments\n");
        std::cerr << "Usage: " << argv[0] << " <PORT NUMBER>" << " [<IP ADDRESS>]\n\nIP ADDRESS defaults to localhost" << std::endl;
        exit(1);
    }

    Client cli((std::string) svraddr, port);
    cli.handle_client(stdin, cli.socket_id);
    (cli.s).close();

    return 0;
}