%{
#include "y.tab.h"
%}

%x cmdload cmdshow

%%

(E|e)(X|x)(I|i)(T|t)		return EXIT;
(H|h)(E|e)(L|l)(P|p)		return HELP;
(L|l)(I|i)(S|s)(T|t)		return LIST;
(S|s)(H|h)(O|o)(W|w)		{ BEGIN cmdshow; return SHOW; }
(L|l)(O|o)(A|a)(D|d)		{ BEGIN cmdload; return LOAD; }

.							{printf("O comando '%s' não foi reconhecido.\nTente escrever 'HELP' para mais informações.\n",yytext);}

<cmdload>[a-zA-Z0-9]+			{yylval.str = strdup(yytext); BEGIN 0; return id; }
<cmdload>([a-zA-Z0-9]+)\.xml	{yylval.str = strdup(yytext); return fichId; }

<cmdshow>[a-zA-Z0-9]+			{yylval.str = strdup(yytext); BEGIN 0; return id;}
<*>[ \n\t]					;

%%
int yywrap(){
	return 1;
}
