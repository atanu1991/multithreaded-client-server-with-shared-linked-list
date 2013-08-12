/*
 * File:   Client.h
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:46 PM
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include "Socket.h"
#include "Helper.h"
#include "Globals.h"
#include <string>

class Client
{
public:
  Client(std::string host, int port);

  Client()
  {
  };
  virtual ~Client();
  Socket s;
  int socket_id;
  void handle_client(FILE *, int);
private:

} ;

#endif	/* CLIENT_H */

