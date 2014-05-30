%{
#include <stdio.h>
#include <stdlib.h>
#include "xmldata.h"

extern int xmllineno;
extern FILE *xmlin;
%}

%token ENDTAGB SINGLETAGE texto id valor
%start Documento

%parse-param {int *xmlfile}

%union {
	char *str;
	AttrList alist;
	NodePtr node;
}


%type <str> ENDTAGB SINGLETAGE texto id valor
%type <alist> AttrList Attr
%type <node> Documento NodeList Node Tag

%%
Documento	: Tag {$$ = $1; xmlfile = $$; };

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
int xmlerror(char *s){
	fprintf(stderr,"%s near %d\n",s,xmllineno);
}

int main(){
	xmlparse();
}

void* parseXmlFile(char *path){
	void* xmlfile = NULL;
	FILE *fp=fopen(path,"r");
 	if(!fp)
 	{
  		printf("O ficheiro não foi encontrado!\n");
 	} else {
		xmlin=fp;
		xmlparse(xmlfile);
		
		fclose(fp);
	}
	return xmlfile;
}

