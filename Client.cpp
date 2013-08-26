/*
 * File:   Client.cpp
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:46 PM
 */

#include "Client.h"

Client::Client(std::string host, int port)
{
  socket_id = s.create();
  printf("CLIENT: Connecting to server %s with port %d\n", host.c_str(), port);
  s.connect(host, port);

}

Client::~Client()
{
}

void Client::handle_client(FILE* fp, int sock_fd)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  printf("Enter A Message or \"exit\" to exit\nmcsll> ");
  while (fgets(sendline, MAXLINE, fp) != NULL)
  {
    n = strlen(sendline);
    if (Helper::writeline(sock_fd, sendline, n) != n)
      std::cerr << ("CLIENT:Write error on socket\n");
    /* read a line from socket,write to standard output */
    n = Helper::readline(sock_fd, recvline, MAXLINE);
    if (n < 0)
      std::cerr << ("CLIENT:Read error on socket\n");
    if (strncmp(recvline, "exit", 4) == 0 || strncmp(recvline, "EXIT", 4) == 0)
      break;
    printf("%s", recvline);
    if (strcmp(recvline, death_msg) == 0)
      break;
    memset(recvline, 0, MAXLINE + 1);
    memset(sendline, 0, MAXLINE + 1);
    std::cout<<"mcsll> "; 
  }
  if (ferror(fp))
  {
    std::cerr << ("CLIENT:Error reading file\n");
  }
  printf("bye\n");
  return;
}
