%{
#include "Globals.h"
#include "yacc_file.tab.hh"

  extern "C"
    {
      int yylex(void);
    }

%}
alpha [A-Za-z]
digit [0-9]

%option case-insensitive
%%

"DELETE ALL"  return DELALL;
"SHOW STATUS" return SHSTAT;
[ \t] ;
INSERT        return INSERT;
DELETE        return DELETE;
FIND          return FIND;

(\+|\-)?[0-9]+\.[0-9]+ { yylval.fval = atof(yytext);  return FLOAT;  }
(\+|\-)?[0-9]+         { yylval.ival = atoi(yytext);  return INT;    }
["\""]+  	       { return QUOTE;}
[a-zA-Z0-9_]+          { yylval.sval = strdup(yytext);return STRING; }
\n                     { return ENDL; }
.    ;

%%
