%{
#include <stdio.h>
%}

%token ENDTAGB SINGLETAGE 
%token texto id valor

%%
Documento	: ElemList '$'  {printf("FIM\n");};

ElemList	: ElemList Elem
			| Elem
			;

Elem		: texto
			| '&' id ';'
			| '<' id AttrList '>' ElemList ENDTAGB id '>'
			| '<' id AttrList SINGLETAGE
			;

AttrList	: Attr AttrList
			|
			;

Attr		: id '=' valor;

%%
int yyerror(char *s){
	fprintf(stderr,"%s",s);
}

int main(){
    yyparse();
	return 0;
}
