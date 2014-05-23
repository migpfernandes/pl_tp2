%{
#include "y.tab.h"
%}

%x cmdload cmdshow

%%

"EXIT"		return EXIT;
"HELP"		return HELP;
"LIST"		return LIST;
"SHOW"		{ BEGIN cmdshow; printf("teste.\n"); return SHOW; }
"LOAD"		{ BEGIN cmdload; return LOAD; }

<cmdload>[a-zA-Z0-9]+			{BEGIN 0; return id; }
<cmdload>([a-zA-Z0-9]+)\.xml	return fichId;

<cmdshow>[a-zA-Z0-9]+			{BEGIN 0; return id;}
<*>[ \n\t]					;

%%
int yywrap(){
	return 1;
}
