/*
 * File:   Server.h
 * Author: atghosh
 *
 * Created on 19 July, 2013, 12:22 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include "Helper.h"
#include "Socket.h"
#include "Globals.h"
#include <signal.h>
#include "LinkedList.cpp"
#include "Lexheader.h"
#include "yacc_file.tab.hh"
#include <map>
#include <sstream>
#include <time.h>

extern LinkedList<std::string> stringlist;
extern LinkedList<int> intlist;
extern LinkedList<float> floatlist;
extern std::map<int, std::pair<std::string, std::string> > client_details;

extern bool ABORT;
extern int serv_port;
extern pthread_mutex_t lock_parse;

void * wait_stdin(void *arg);
void * process_request(void *arg);
int yyparse(void *);

class Server
{
public:
  Server(int port);

  Server()
  {
  };
  virtual ~Server();
  void start_listening();
  void populate_lists();
  Socket s;
  time_t rawtime;
  static void insert_operation(struct parsed_vals *, std::string &);
  static void find_operation(struct parsed_vals *, std::string &);
  static void delete_operation(struct parsed_vals *, std::string &);
  static void delete_all_operation();

private:
  pthread_t stdin_thread;               /* Thread to handle server side inputs */
  pthread_t process_thread;             /* Thread to process each client request */

} ;
#endif	/* SERVER_H */
