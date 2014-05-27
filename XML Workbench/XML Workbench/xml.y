%{
#include <stdio.h>
#include "xmldata.h"

extern int yylineno;
%}


%token ENDTAGB SINGLETAGE texto id valor
%start Documento

%union {
	char *str;
	AttrList alist;
	NodePtr node;
}


%type <str> ENDTAGB SINGLETAGE texto id valor
%type <alist> AttrList Attr
%type <node> Documento NodeList Node Tag

%%
Documento	: Tag {$$ = $1;showNodeXML($1,"",1);};

Tag			: '<' id AttrList '>' NodeList ENDTAGB id '>' {$$ =consNodefromElem(consElemNode($2,$3,NULL,$5));}; 

AttrList	: AttrList	Attr {$$ = add2AttrList($1,$2);}
			|	{ $$ = NULL;}
			;

Attr		: id '=' valor {$$ = consAttrList($1,$3,NULL);}; 

NodeList	: NodeList Node { $$ = add2NodeList($1,$2); } 
			| Node { $$ = $1; }
			;


Node		: texto   { $$ = consNodefromText(consTextNode($1,NULL)); /* contents,sibling */ }
			| Tag  { $$ = $1;}   
			| '<' id AttrList SINGLETAGE { consNodefromEmptyElem(consEmptyElemNode($2,$3,NULL)); }	
			;

%%
int yyerror(char *s){
	fprintf(stderr,"%s near %d\n",s,yylineno);
}

int main(){
    yyparse();
	return 0;
}
