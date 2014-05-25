%{
#include <string.h>
#include "y.tab.h"
%}

%x intag atr endtag

%%

\<\/		{BEGIN endtag; return ENDTAGB;}
\<			{BEGIN intag; return '<';}
[^\<\>]*	{return texto;}

<intag>[\_a-zA-Z][\_a-zA-Z0-9]*			{ yylval.str = strdup(yytext); BEGIN atr; return id;}

<endtag>[\_a-zA-Z][\_a-zA-Z0-9]*		{ yylval.str = strdup(yytext); return id; }
<endtag>\>								{ BEGIN 0; return '>'; }

<atr>[a-zA-Z][a-zA-Z0-9]*				{ yylval.str = strdup(yytext); return id;}
<atr>\=								return '=';
<atr>\"[~\"]*\"						{ yylval.str = strdup(yytext); return valor; }
<atr>\>								{ BEGIN 0; return '>';}
<atr>\/\>								{ BEGIN 0; return SINGLETAGE;}

<<EOF>>		{ static int once = 0; return once++ ? 0 : '$' ;}

%%
int yywrap(){
	return 1;
}
