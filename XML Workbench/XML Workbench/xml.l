%{
#include "xmldata.h"
#include "xml.tab.h"
#include <string.h>
%}

%x intag atr endtag

%%

\<\/		{BEGIN endtag; return ENDTAGB;}
\<			{BEGIN intag; return '<';}
[^\<]*  	{xmllval.str = strdup(xmltext); return texto;}
[ \n\t]		;

<intag>[a-zA-Z0-9][\_a-zA-Z0-9]*			{ xmllval.str = strdup(xmltext); BEGIN atr; return id;}

<endtag>[a-zA-Z0-9][\_a-zA-Z0-9]*		{ xmllval.str = strdup(xmltext); return id; }
<endtag>\>[ \n\t\r]* 					{ BEGIN 0; return '>'; }

<atr>[a-zA-Z][a-zA-Z0-9\_\-]*			{ xmllval.str = strdup(xmltext); return id;}
<atr>\=									return '=';
<atr>\"[~\"]*\"							{ xmllval.str = strdup(xmltext); return valor; }
<atr>\>[ \n\t\r]*						{ BEGIN 0; return '>';}
<atr>\/\>[ \n\t\r]*						{ BEGIN 0; return SINGLETAGE;}

%%
int xmlwrap(){
//	return 1;
}
