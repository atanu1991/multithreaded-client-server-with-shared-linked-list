/*
 * File:   Server.cpp
 * Author: atghosh
 *
 * Created on 19 July, 2013, 12:36 PM
 */

#include "Server.h"

/* Global variables required by the server */

std::map<int, std::pair<std::string, std::string> > client_details; /* Store all client details */
pthread_mutex_t lock_parse = PTHREAD_MUTEX_INITIALIZER;             /* Thread to lock parser access */
bool ABORT = 0;                                                     /* Is server aborted? */
int serv_port = -1;                                                 /* Port number to run the server on */

/* Three LinkedLists */
LinkedList<std::string> stringlist;
LinkedList<int> intlist;
LinkedList<float> floatlist;

Server::Server(int port)
{

  printf("Starting the Server With Port(%d)\n", port);
  /* create a listening socket */
  serv_port = s.create();
  /* bind our socket address to the listening socket */
  s.bind(port);
}

Server::~Server()
{
}

/*
 Unpack the struct.
 Insert into LinkedList.
 Write confirmation message into the string.

 @param parm structured containing parsed query
 @param msg to store the message
 */

void Server::insert_operation(struct parsed_vals * parm, std::string &msg)
{
  std::stringstream msg_stream;
  bool success = false;
  switch (parm->type) {
  case INT_TYPE:
    if (intlist.addNode((parm->data).int_data))
    {
      msg_stream << (parm->data).int_data << " successfully inserted into the list\n";
      success = true;
    }
    break;
  case FLOAT_TYPE:
    if (floatlist.addNode((parm->data).float_data))
    {
      msg_stream << (parm->data).float_data << " successfully inserted into the list\n";
      success = true;
    }
    break;
  case STRING_TYPE:
    if (stringlist.addNode((parm->data).str_data))
    {
      msg_stream << (parm->data).str_data << " successfully inserted into the list\n";
      success = true;
    }
    break;
  }
  if (!success)
    msg_stream << "Insertion failed due to a reason I couldn't figure out.\
Would you mind trying again?\n";
  msg = msg_stream.str();
}

/*
 Unpack the struct.
 Delete value from  LinkedList.
 Write confirmation message into the string.

 @param parm structured containing parsed query
 @param msg to store the message
 */

void Server::delete_operation(struct parsed_vals * parm, std::string &msg)
{
  std::stringstream msg_stream;
  bool success = false;
  switch (parm->type) {
  case INT_TYPE:
    if (intlist.deleteNode((parm->data).int_data))
    {
      msg_stream << (parm->data).int_data << " successfully deleted\n";
      success = true;
    }
    break;
  case FLOAT_TYPE:
    if (floatlist.deleteNode((parm->data).float_data))
    {
      msg_stream << (parm->data).float_data << " successfully deleted\n";
      success = true;
    }
    break;
  case STRING_TYPE:
    if (stringlist.deleteNode((parm->data).str_data))
    {
      msg_stream << (parm->data).str_data << " successfully deleted\n";
      success = true;
    }
    break;
  }
  if (!success)
    msg_stream << "Deletion failed as the element was not found in the list.\
Why don't you try inserting it?\n";
  msg = msg_stream.str();
}

/*
 Unpack the struct.
 Check if value exists in LinkedList.
 Write confirmation message into the string.

 @param parm structured containing parsed query
 @param msg to store the message
 */

void Server::find_operation(struct parsed_vals * parm, std::string &msg)
{
  std::stringstream msg_stream;
  bool success = false;
  switch (parm->type) {
  case INT_TYPE:
    if (intlist.check_if_exists((parm->data).int_data))
    {
      msg_stream << (parm->data).int_data << " found in the list\n";
      success = true;
    }
    break;
  case FLOAT_TYPE:
    if (floatlist.check_if_exists((parm->data).float_data))
    {
      msg_stream << (parm->data).float_data << " found in the list\n";
      success = true;
    }
    break;
  case STRING_TYPE:
    if (stringlist.check_if_exists((parm->data).str_data))
    {
      msg_stream << (parm->data).str_data << " found in the list\n";
      success = true;
    }
    break;
  }
  if (!success)
    msg_stream << "This value wasn't found in the list! Why don't you try inserting it?\n";
  msg = msg_stream.str();
}

void Server::delete_all_operation()
{
  intlist.destroyList();
  floatlist.destroyList();
  stringlist.destroyList();
}

/*
 serves each client request

 @parm cli_id client id --> return value from accept
 */
void * process_request(void *cli_id)
{
  int tmp = *((int *) cli_id);
  free(cli_id);
  pthread_detach(pthread_self());
  int clientsocket = tmp;
  char buffer[MAXLINE];
  std::string mssg;
  while (!ABORT)
  {
    if (Helper::readline(clientsocket, buffer, MAXLINE - 1) < 0)
    {
      break;
    }
    /* check if the command is exit.is yes, close this thread */
    if (strncmp(buffer, "EXIT", 4) == 0 || strncmp(buffer, "exit", 4) == 0)
    {
      Helper::writeline(clientsocket, buffer, sizeof buffer);
      break;
    }

    /* lock the parsing operation */
    pthread_mutex_lock(&lock_parse);
    struct parsed_vals tokens;
    YY_BUFFER_STATE bp = yy_scan_string(buffer);
    yy_switch_to_buffer(bp);
    int ret_val = yyparse((void *) &tokens);
    yy_delete_buffer(bp);
    pthread_mutex_unlock(&lock_parse);

    /* call required function based on the 'cmd; field of struct (here tokens)*/

    if (ret_val == 0)
    {
      switch (tokens.cmd) {
      case INSERT_CMD:
        Server::insert_operation(&tokens, mssg);
        break;
      case FIND_CMD:
        Server::find_operation(&tokens, mssg);
        break;
      case DELETE_CMD:
        Server::delete_operation(&tokens, mssg);
        break;
      case DELALL_CMD:
        Server::delete_all_operation();
        mssg = "All items successfully deleted\n";
        break;
      case SHOW_CMD:
        std::stringstream msg;
        msg << intlist.size << " integers\t" << floatlist.size << " \
floats\t" << stringlist.size << " strings\n";
        mssg = msg.str();
        break;
      }
    } else
    {
      mssg = "Invalid command issued!!!\n";
    }

    if (Helper::writeline(clientsocket, (char *) (mssg.c_str()), mssg.length()) < 0)
    {
      break;
    }
    memset(buffer, 0, sizeof buffer);
  }
  client_details.erase(clientsocket);
  if (::close(clientsocket) < 0)
  {
    std::cerr << "Error in calling close\n";
  }
  pthread_exit(NULL);
}

void* wait_stdin(void *arg)
{
  pthread_detach(pthread_self());
  std::string text;
  while (1)
  {
    std::getline(std::cin, text);
    if (0 == text.compare("show client details") || 0 == text.compare("SHOW CLIENT DETAILS"))
    {
      std::map<int, std::pair<std::string, std::string> >::iterator iter = client_details.begin();
      bool atleast_one=false;
      for (iter = client_details.begin(); iter != client_details.end(); ++iter)
      {
        std::cout << (iter->second).first << ":" << (iter->second).second << '\n';
        atleast_one = true;
      }
      if (!atleast_one)
        std::cout << "No clients connected\n";
    } else
    {
      std::cout << "Invalid Command Issued\nTry \"show client details\"\n";
    }
  }
  pthread_exit(NULL);

}

void Server::start_listening()
{
  s.listen();
  if ((pthread_create(&stdin_thread, NULL, &wait_stdin, NULL)) != 0) /* create new thread for server stdin input */
  {
    std::cerr << ("SERVER:Error Creating A thread for stdin\n");
    exit(EXIT_FAILURE);
  }
  std::string cli_name;
  while (1)
  {

    int *conn_s;
    std::string time_accept;
    conn_s = (int *) malloc(sizeof (int));
    cli_name = s.accept(conn_s);

    /* Insert into map details of all clients */
    time(&rawtime);
    time_accept = ctime(&rawtime);

    client_details.insert(std::make_pair(*conn_s, std::make_pair(cli_name, time_accept)));

    if ((pthread_create(&process_thread, NULL, &process_request, conn_s)) != 0) /* new thread for each client */
    {
      std::cerr << ("SERVER:Error Creating A thread for Socket(%d)\n",
              *conn_s);
      exit(EXIT_FAILURE);
    }
  }
}

/*
 Populate the list on server startup.
 Data persistency.
 */
void Server::populate_lists()
{

  intlist.fillList(INT_FILE_PATH);
  floatlist.fillList(FLOAT_FILE_PATH);
  stringlist.fillList(STRING_FILE_PATH);

}
