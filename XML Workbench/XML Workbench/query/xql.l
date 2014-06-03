%{
#include "y.tab.h"
%}

%%
\[		return '[';
\]		return ']';
\/		return SLASH;
\*		return '*';

(\.\/|\/\/)[a-zA-Z0-9]+   { yylval.str = strdup(yytext+2); return name; }
[a-zA-Z0-9]+              { yylval.str = strdup(yytext); return name; }
\@[a-zA-Z0-9]+			{ yylval.str = strdup(yytext+1); return atrib; }

\n                       	{ return END; }
[ \t]						;

%%

int yywrap(){
	return 0;
}
