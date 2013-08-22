#include "Socket.h"
#include "SocketException.h"

Socket::Socket() :
m_sock(-1)
{

  memset(&m_addr,
         0,
         sizeof ( m_addr));

}

Socket::~Socket()
{
  if (is_valid())
    ::close(m_sock);
}

int Socket::create()
{
  m_sock = socket(AF_INET,
                  SOCK_STREAM,
                  0);

  if (!is_valid())
    throw SocketException("Could not create listening socket.\n");

  return m_sock;

}

int Socket::bind(const int port)
{

  if (!is_valid())
  {
    return false;
  }

  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons(port);

  int bind_return = ::bind(m_sock,
                           (struct sockaddr *) &m_addr,
                           sizeof ( m_addr));

  if (bind_return == -1)
  {
    throw SocketException("Could not bind to this port. May be in use!\n");
  }

  return bind_return;
}

int Socket::listen() const
{
  if (!is_valid())
  {
    return false;
  }

  int listen_return = ::listen(m_sock, LISTENQ);

  if (listen_return == -1)
  {
    throw SocketException("Could not listen to socket.\n");
  }

  return listen_return;
}

/*
  accept the client connection and determines  its IP

  SYNOPSIS
  acc_ret stores the client id

  NOTES
    The client id is stored in acc_ret,
    the IP address is calculated and returned

  RETURN
    string  client IP address
 */

std::string Socket::accept(int *acc_ret) const
{

  struct sockaddr_in clientaddr;
  int sizeofclientaddr;
  sizeofclientaddr = sizeof (clientaddr);
  int ret_val = ::accept(m_sock, (struct sockaddr *) & (clientaddr), (socklen_t *) & sizeofclientaddr);

  if (ret_val <= 0)
    throw SocketException("Could not create client socket due to an unexpected error.\n");
  else
  {
    *acc_ret = ret_val;
    char clntName[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clntName,
                  sizeof (clntName)) == NULL)
      std::cerr << ("Error in retrieving client address details!");
    std::string client_name(clntName);
    return client_name;
  }
}

bool Socket::connect(const std::string host, const int port)
{

  if (!is_valid()) return false;

  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(port);

  int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

  if (errno == EAFNOSUPPORT) return false;

  status = ::connect(m_sock, (sockaddr *) & m_addr, sizeof ( m_addr));

  if (status == 0)
    return true;
  else
    throw SocketException("Client Cannot Connect To Server (Invalid Port or Server Problem)\n");
}

int Socket::close()
{
  if (::close(m_sock) != 0)
    throw SocketException("Call to close failed due to an error (Wrong file-descriptor or I/O error)\n");
  return 0;
}
