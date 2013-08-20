#ifndef Helper_class
#define Helper_class

#include <unistd.h>
#include <stdio.h>

class Helper
{
public:
  Helper();

  /* Helper functions */
  static int readline(int, char *, int);
  static int writeline(int, char *, int);
} ;
#endif
