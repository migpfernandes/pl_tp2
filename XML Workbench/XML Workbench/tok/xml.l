%{
#include "y.tab.h"
#include <string.h>
%}

%x intag atr endtag

%%

\<\/		{BEGIN endtag; return ENDTAGB;}

\<			{BEGIN intag; return '<';}
[^\<]*		{printf("###%s###\n",yytext); return texto;}

<intag>[\_a-zA-Z][\_a-zA-Z0-9]*			{ BEGIN atr; return id;}

<endtag>[\_a-zA-Z][\_a-zA-Z0-9]*		{ return id; }
<endtag>\>[ \n\t\r]*						{BEGIN 0; return '>'; }

<atr>[a-zA-Z][a-zA-Z0-9\_\-]*				{ return id;}
<atr>\=								return '=';
<atr>\"[~\"]*\"						{ return valor; }
<atr>\>[ \n\t\r]*						{ BEGIN 0; return '>';}
<atr>\/\>[ \n\t\r]*					{ BEGIN 0; return SINGLETAGE;}


%%
int yywrap(){
	//return 1;
}
