/*
 * File:   client_main.cpp
 * Author: atghosh
 *
 * Created on 19 July, 2013, 9:47 PM
 */

#include "Server.h"

/*
 Handles the SIGINT signal

 @param signum signal number to be handled

 NOTES

 Operations performed::
 Send message to all the client that server is shut.
 Close opened ports.
 Writes data in Linked-List to tmp file.

 */

void signal_Handler(int signum)
{

  if (!client_details.size())
  {
    ABORT = 1;
    std::map<int, std::pair<std::string, std::string> >::iterator iter = client_details.begin();
    for (iter = client_details.begin(); iter != client_details.end(); ++iter)
    {
      Helper::writeline(iter->first, (char *) death_msg, sizeof death_msg);
    }
    ::close(serv_port);

    intlist.printList(INT_FILE_PATH);
    floatlist.printList(FLOAT_FILE_PATH);
    stringlist.printList(STRING_FILE_PATH);

    exit(0);
  } else
  {
    std::cout << "\nClients connected.Can't ABORT server.\n";
  }
}

int main(int argc, char *argv[])
{
  short int port;                               /*port number */
  char *endptr;                                 /*for strtol() */

  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, signal_Handler);
  signal(SIGTERM, signal_Handler);

  /* Check the number of parameters */
  if (argc != 2)
  {
    /** Tell the user how to run the program
        Exactly 2 arguments expected: the program name,
        the port number to start the server on.
     */

    std::cerr << "Usage: " << argv[0] << " <PORT NUMBER>" << std::endl;
    return 1;
  }
  if (argc == 2)
  {
    port = strtol(argv[1], &endptr, 0);
    if (*endptr)
    {
      printf("SERVER :Invalid port Number\n");
      exit(EXIT_FAILURE);
    }
  }

  Server sv(port);
  sv.populate_lists();
  sv.start_listening();

  return 0;
}
