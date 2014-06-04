%{
#include "list.h"
#include "xmlpath.h"
#include "y.tab.h"
%}

%x cmdload cmdshow cmdunknown cmdqle queryexp

%%

(E|e)(X|x)(I|i)(T|t)		return EXIT;
(H|h)(E|e)(L|l)(P|p)		return HELP;
(L|l)(I|i)(S|s)(T|t)		return LIST;
(S|s)(H|h)(O|o)(W|w)		{ BEGIN cmdshow; return SHOW; }
(L|l)(O|o)(A|a)(D|d)		{ BEGIN cmdload; return LOAD; }
(Q|q)(L|l)(E|e)(\:\ )			{BEGIN cmdqle; return QLE; }

[a-zA-Z]+					{
								BEGIN cmdunknown; 
								yylval.str = strdup(yytext);
								printf("O comando '%s' não foi reconhecido.\nTente escrever 'HELP' para mais informações.\n",yytext);
								return UNKNOWN; 
							}
.							;

<cmdload>[a-zA-Z0-9]+				{yylval.str = strdup(yytext); BEGIN 0; return id; }
<cmdload>[a-zA-Z0-9\-\_/\.][a-zA-Z0-9\-\_/ \.]+\.xml	{yylval.str = strdup(yytext); return fichId; }
<cmdload>\"[^\"]+\"					{yylval.str = strdup(yytext+1); yylval.str[strlen(yylval.str)-1] = '\0'; return fichId; }

<cmdshow>[a-zA-Z0-9]+			{yylval.str = strdup(yytext); BEGIN 0; return id;}

<cmdqle>,						{return ','; }
<cmdqle>\*						{return '*'; BEGIN queryexp; }
<cmdqle>[a-zA-Z0-9]+			{yylval.str = strdup(yytext); return id; }
<cmdqle>[ \t]					{BEGIN queryexp; }
<cmdqle>.						;

<queryexp>\/\/      return DOUBLESLASH;
<queryexp>\[		return '[';
<queryexp>\]		return ']';
<queryexp>\/		return SLASH;
<queryexp>\*		return '*';
<queryexp>\.		return PERIOD;

<queryexp>[a-zA-Z0-9]+              { yylval.str = strdup(yytext); return tagname; }
<queryexp>\@[a-zA-Z0-9]+			{ yylval.str = strdup(yytext+1); return atribname; }

<queryexp>\n                       	{ BEGIN 0; return END; }
<queryexp>[ \t]						;

<cmdunknown>.					;
<cmdunknown>\n					{ BEGIN 0; }

<*>[ \n\t]					;

%%
int yywrap(){
	return 1;
}
