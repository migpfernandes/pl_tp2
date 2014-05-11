%{
#include "y.tab.h"
%}

%x intag atrib endtag

%%

\<\/		{BEGIN endtag; return ENDTAGB;}
\<			{BEGIN intag; return '<';}
[^\<\>]*	{return texto;}

<intag>[\_a-zA-Z][\_a-zA-Z0-9]*			{ BEGIN atrib; return id;}

<endtag>[\_a-zA-Z][\_a-zA-Z0-9]*		return id;
<endtag>\>								{BEGIN 0; return '>'; }

<atrib>[a-zA-Z][a-zA-Z0-9]*				return id;
<atrib>\=								return '=';
<atrib>\"[~\"]*\"						return valor;
<atrib>\>								{ BEGIN 0; return '>';}
<atrib>\/\>								{ BEGIN 0; return SINGLETAGE;}

<<EOF>>		{ static int once = 0; return once++ ? 0 : '$' ;}

%%
int yywrap(){
	return 1;
}
