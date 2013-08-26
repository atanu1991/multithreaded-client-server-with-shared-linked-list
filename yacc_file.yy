%{
#include "Globals.h"
#define YYPARSE_PARAM parm
#define cast ((struct parsed_vals *) parm)


void yyerror(const char *s)
{
  fprintf(stderr, "error: %s\n", s);
}
extern "C"
{
  int yylex(void);
  int yywrap()
  {
    return 1;
  }
}
%}

%token INSERT DELETE DELALL FIND ENDL SHSTAT QUOTE
%union {
  int ival;
  float fval;
  char *sval;
}

%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%%

S:T

T:      INSERT val  {cast->cmd=INSERT_CMD;}
      | DELETE val  {cast->cmd=DELETE_CMD;}
      | DELALL ENDL {cast->cmd=DELALL_CMD;}
      | FIND val    {cast->cmd=FIND_CMD;  }
      | SHSTAT ENDL {cast->cmd=SHOW_CMD;  }
;

val :   INT ENDL    {cast->type=INT_TYPE;
		    	(cast->data).int_data=$1;  }
      |
        FLOAT ENDL  {cast->type=FLOAT_TYPE;
			(cast->data).float_data=$1;}
      |
        STRING ENDL {cast->type=STRING_TYPE;
			(cast->data).str_data=$1;  }

      | QUOTE STRING QUOTE ENDL {cast->type=STRING_TYPE;
			(cast->data).str_data=$2;  }
;

%%
