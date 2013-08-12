// Implementation of the Helper class
#include "Helper.h"

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
