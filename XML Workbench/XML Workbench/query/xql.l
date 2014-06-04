%{
#include "list.h"
#include "xmlpath.h"
#include "y.tab.h"
%}

%%
\/\/	return DOUBLESLASH;
\[		return '[';
\]		return ']';
\/		return SLASH;
\*		return '*';
\.		return PERIOD;

[a-zA-Z0-9]+              { yylval.str = strdup(yytext); return tagname; }
\@[a-zA-Z0-9]+			{ yylval.str = strdup(yytext+1); return atribname; }

\n                       	{ return END; }
[ \t]						;

%%

int yywrap(){
	return 0;
}
