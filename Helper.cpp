#include "Helper.h"

/*
  read the string from the file descriptor and store it in buffer

  @param fd     file-descriptor
  @parma ptr    buffer to store the data read from fd
  @parma maxlen maximum number of characters to read

  RETURN
    int  the number of characters read
 */

int Helper::readline(int fd, char *ptr, int maxlen)
{
  int n, rc;
  char c;
  char *bufptr = ptr;
  for (n = 1; n < maxlen; n++)
  {
    if ((rc = read(fd, &c, 1)) == 1)
    {
      *bufptr++ = c;
      if (c == '\n')
        break;
    } else if (rc == 0)
    {
      if (n == 1)
        return 0;
      else
        break;
    } else
      return (-1);
  }
  *bufptr = 0;
  return (n);
}

/*
  read nbytes from the buffer and write to fd

  @param fd     file-descriptor
  @parma ptr    buffer containing data
  @parma nbytes maximum number of bytes to read

  RETURN
    int  the number of characters written
 */

int Helper::writeline(int fd, char *ptr, int nbytes)
{
  int nleft, nwritten;
  char *bufptr = ptr;
  nleft = nbytes;
  while (nleft > 0)
  {
    nwritten = write(fd, bufptr, nleft);
    if (nwritten <= 0)
      return nwritten;
    nleft -= nwritten;
    bufptr += nwritten;
  }
  return (nbytes - nleft);
}
