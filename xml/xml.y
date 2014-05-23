%{
#include <stdio.h>
#include "xml.h"
%}

%union{
	char *str;
	Attr at;
	AttrList atribs;
	Elem element;
	ElemList elementList;
	Tag tags;
}

%token ENDTAGB SINGLETAGE 
%token texto id valor
%start Documento

%type <str> ENDTAGB SINGLETAGE texto id valor
%type <at> Attr
%type <atribs> AttrList
%type <element> Elem
%type <elementList> ElemList
%type <tags> Tag Documento

%%
Documento	: Tag  {$$ = $1;};

Tag			: '<' id AttrList '>' ElemList ENDTAGB id '>'   { $$ = cons_Tag($2,$3,$5);} ;

ElemList	: ElemList Elem		{ $$ = cons_ElemList( $1, $2);}
			| Elem		{ $$ = cons_ElemList_Elem($1);}
			;

Elem		: texto   {$$ = cons_Elem_Texto($1);}
			| '&' id ';'	{$$ = cons_Elem_Reservada($2);}
			| Tag     { $$ = $1; }
			| '<' id AttrList SINGLETAGE 	{$$ = cons_Elem_SimpleTag($2, $3);}
			;

AttrList	: Attr AttrList		{$$ = cons_AttrList($1, $2);}
			|	{$$ = cons_AttrList_NIL();}
			;

Attr		: id '=' valor {$$ = cons_Atribs($1, $3);};

%%
int yyerror(char *s){
	fprintf(stderr,"%s",s);
}

int main(){
    yyparse();
	return 0;
}
