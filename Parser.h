#include <iostream>
#include <string.h>

enum CMD
{
  INSERT_CMD = 1, DELETE_CMD, FIND_CMD, DELALL_CMD, SHOW_CMD
} ;

enum TYPE
{
  INT_TYPE = 6, FLOAT_TYPE, STRING_TYPE
} ;

/*  Structure to be sent to the parser to store the return values */
struct parsed_vals
{
  int cmd;
  int type;

  union
  {
    int int_data;
    float float_data;
    char *str_data;
  } data;
} ;

class Parser
{
public:
  void* scanner;
  struct parsed_vals PV;
  const char * buffer;

public:

  Parser (const char *input)
  {
    init_scanner();
    buffer = input;

  }

  virtual ~Parser ()
  {
    destroy_scanner();
  }

  // Defined in lex_file.l
protected:
  void init_scanner();
  void destroy_scanner();
} ;


int yyparse(Parser*);

Parser *yyget_extra(void *yyscanner);
Parser yyset_extra(void *dat, void *yyscanner);

