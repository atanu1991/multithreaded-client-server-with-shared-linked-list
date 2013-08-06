/* 
 * File:   Client.cpp
 * Author: atghosh
 * 
 * Created on 19 July, 2013, 9:46 PM
 */

#include "Client.h"
#include "Socket.h"
#include "Helper.h"
#include "SocketException.h"
#include "Globals.h"

Client::Client(std::string host, int port) {
    // Create a listening socket
    socket_id = s.create();
    printf("\nCLIENT: Connecting to server %s with port %d", host.c_str(), port);
    s.connect(host, port);

}

Client::~Client() {
}

void Client::handle_client(FILE* fp, int sock_fd) {
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    printf("\nEnter A Message or \"exit\" to exit\n");
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        n = strlen(sendline);
        if (Helper::writeline(sock_fd, sendline, n) != n)
            throw SocketException("CLIENT:Write error on socket\n");
        /*read a line from socket,write to standard output*/
        n = Helper::readline(sock_fd, recvline, MAXLINE);
        if (n < 0)
            throw SocketException("CLIENT:Read error on socket\n");
        if (strncmp(recvline, "exit", 4) == 0)
            break;
        printf("%s", recvline);
        if (strcmp(recvline, death_msg) == 0)
            break;
        memset(recvline, 0, MAXLINE + 1);
        memset(sendline, 0, MAXLINE + 1);
    }
    if (ferror(fp)) {
        std::cerr << ("CLIENT:Error reading file\n");
    }
    return ;
}
