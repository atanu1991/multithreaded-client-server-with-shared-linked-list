%pure-parser
%locations
%defines
%error-verbose
%parse-param   { Parser* context }
%lex-param     { void* scanner  }

%token INSERT DELETE DELALL FIND ENDL SHSTAT QUOTE
%union {
  int ival;
  float fval;
  char *sval;
}

%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%{
	#include "Parser.h"

	int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);

	void yyerror(YYLTYPE* locp, Parser* context, const char* err)
	{
		std::cout << locp->first_line << ":" << err << std::endl;
	}

	#define scanner context->scanner

	#define cast (context->PV)
%}

%%

start:T

T:      INSERT val
      | DELETE val
      | DELALL ENDL {cast.cmd=DELALL_CMD;return 0;}
      | FIND val
      | SHSTAT ENDL {cast.cmd=SHOW_CMD;  return 0;}
;

val :   INT ENDL    {cast.type=INT_TYPE;
		    	(cast.data).int_data=$1;  return 0;}
      |
        FLOAT ENDL  {cast.type=FLOAT_TYPE;
			(cast.data).float_data=$1;return 0;}
      |
        STRING ENDL {cast.type=STRING_TYPE;
			(cast.data).str_data=$1;  return 0;}

      | QUOTE STRING QUOTE ENDL {cast.type=STRING_TYPE;
			(cast.data).str_data=$2;  return 0;}
;
%%