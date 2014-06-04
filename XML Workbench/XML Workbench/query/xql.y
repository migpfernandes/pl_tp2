%{
#include <stdio.h>
#include "list.h"
#include "xmlpath.h"
%}

%token tagname atribname END SLASH DOUBLESLASH ERROR PERIOD
%start Xql

%union {
	char* str;
	NODE* list;
	XmlPath pathxml;
	int num;
}

%type<str> tagname atribname END
%type<num> Context Context2
%type<list> QueryExp2 QueryExp TagList FilterList Filter
%type<pathxml> Tag

%%
Xql			: Run;

Run			: Run QueryExp2 END { printf("Passou no Xql1.\n"); printXpathExpression($2); }
			| QueryExp2 END  { printf("Passou no Xql2.\n"); printXpathExpression($1); }
			;

Context		: Context2		{ $$ = $1; }
			| 				{ $$ = 0; }
			;

Context2	: SLASH			{ $$ = 1; }
			| DOUBLESLASH   { $$ = 2; }
			;

QueryExp2	: PERIOD QueryExp  { setDirectChild($2,1); $$ = $2; }
			| QueryExp { $$ = $1; }
			;

QueryExp	: TagList Context2 atribname 	{ XmlPath atribNode = createXmlNode($3,NULL,1,$2); $$ = addXmlPathNode($1,atribNode); }
			| Context atribname 			{ XmlPath atribNode = createXmlNode($2,NULL,1,$1); $$ = addXmlPathNode(NULL,atribNode); }
			| TagList  						{ $$ = $1; }
			;

TagList		: TagList Context2 Tag	{ $3->slashPrefixNo = $2; $1 = addXmlPathNode($1,$3); $$ = $1; }
			| Context Tag			{ $2->slashPrefixNo = $1; $$ = addXmlPathNode(NULL,$2); }
			;

Tag			: tagname FilterList	{ $$ = createXmlNode($1, $2,0,0); }
			| '*' FilterList	  	{ $$ = createXmlNode("*", $2,0,0); }
			;

FilterList	: FilterList Filter {
									NODE* atribs = $1;
									if (!atribs) atribs = list_create($2);
									else atribs = list_insert_after(atribs,$2);
									$$ = atribs;
								}
			| 					{ $$ = NULL; }
			;

Filter		: '[' QueryExp2 ']' {$$ = $2; }

%%

int yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}

int main(){
	yyparse();
	return 1;
}
