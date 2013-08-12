// Definition of the Socket class

#ifndef Socket_class
#define Socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>

#define MAXLINE 10000
#define LISTENQ 	(1024)
#define SERV_HOST_ADDR "127.0.0.1"

class Socket
{
public:
  Socket();
  virtual ~Socket();

  // Server initialization
  int create();
  int bind(const int port);
  int listen() const;

  // Custom accept function -- Returns IP address of connect client
  std::string accept(int *) const;
  // Client initialization
  bool connect(const std::string host, const int port);

  bool is_valid() const
  {
    return m_sock != -1;
  }

  int close();
  int m_sock;

private:
  struct sockaddr_in m_addr;

} ;

#endif
