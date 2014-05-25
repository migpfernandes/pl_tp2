%{
#include <stdio.h>
%}

%union{
	char *str;
	
}

%token ENDTAGB SINGLETAGE texto id valor
%start Documento

%%
Documento	: Tag;

Tag			: '<' id AttrList '>' NodeList ENDTAGB id '>';

AttrList	: AttrList	Attr	
			|	
			;

Attr		: id '=' valor; 

NodeList	: NodeList Node
			| Node
			;


Node		: texto   
			| Tag     
			| '<' id AttrList SINGLETAGE 	
			;

%%
int yyerror(char *s){
	fprintf(stderr,"%s",s);
}

int main(){
    yyparse();
	return 0;
}
