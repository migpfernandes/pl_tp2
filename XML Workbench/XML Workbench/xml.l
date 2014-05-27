%{
#include "xmldata.h"
#include "y.tab.h"
#include <string.h>
%}

%x intag atr endtag

%%

\<\/		{BEGIN endtag; return ENDTAGB;}
\<			{BEGIN intag; return '<';}
[^\<]*  	{yylval.str = strdup(yytext); return texto;}
[ \n\t]		;

<intag>[\_a-zA-Z][\_a-zA-Z0-9]*			{ yylval.str = strdup(yytext); BEGIN atr; return id;}

<endtag>[\_a-zA-Z][\_a-zA-Z0-9]*		{ yylval.str = strdup(yytext); return id; }
<endtag>\>[ \n\t\r]* 					{ BEGIN 0; return '>'; }

<atr>[a-zA-Z][a-zA-Z0-9\_\-]*			{ yylval.str = strdup(yytext); return id;}
<atr>\=									return '=';
<atr>\"[~\"]*\"							{ yylval.str = strdup(yytext); return valor; }
<atr>\>[ \n\t\r]*						{ BEGIN 0; return '>';}
<atr>\/\>[ \n\t\r]*						{ BEGIN 0; return SINGLETAGE;}

%%
int yywrap(){
//	return 1;
}
