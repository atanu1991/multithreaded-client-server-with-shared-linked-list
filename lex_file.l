%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno
%option case-insensitive

%{
	#include "Parser.h"
	#include "yacc_file.tab.h"

	#define YY_EXTRA_TYPE Parser*
	#define YY_USER_ACTION yylloc->first_line = yylineno;

	#define YY_INPUT(buf,result,max_size) \
	{ memcpy(buf,(*yyextra).buffer,strlen((*yyextra).buffer));\
	  result=strlen((*yyextra).buffer); \
	}


%}

%%

"DELETE ALL"  return DELALL;
"SHOW STATUS" return SHSTAT;
[ \t] ;
"INSERT"      {(yyextra->PV).cmd=INSERT_CMD; return INSERT;}
"DELETE"      {(yyextra->PV).cmd=DELETE_CMD; return DELETE;}
"FIND"        {(yyextra->PV).cmd=FIND_CMD;   return FIND;  }

(\+|\-)?[0-9]+\.[0-9]+ { yylval->fval = atof(yytext);  return FLOAT;  }
(\+|\-)?[0-9]+         { yylval->ival = atoi(yytext);  return INT;    }
["\""]+  	       { return QUOTE;}
[a-zA-Z0-9_]+          { yylval->sval = strdup(yytext);return STRING; }
\n                     { return ENDL; }
.    ;

%%

void Parser::init_scanner()
{
	yylex_init(&scanner);
	yyset_extra(this, scanner);
}

void Parser::destroy_scanner()
{
	yylex_destroy(scanner);
}