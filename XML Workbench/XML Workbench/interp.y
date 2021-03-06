%{
#include <stdio.h>
#include "FileInfo.h"
#include "global.h"
#include "list.h"
#include "xmlpath.h"

#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

NODE* list=NULL;
extern int parseXmlFile(char* path);

NodePtr xmlFile=NULL;
int errorOcurred;

void showHelpMessage();
void showPrompt();
int printStringList(void *s);
%}

%token LOAD SHOW LIST EXIT HELP QLE UNKNOWN END SLASH DOUBLESLASH ERROR PERIOD
%token fichId id tagname atribname
%start Interp

%union{
	char *str;
	NODE* no;
	XmlPath pathxml;
	int num;
}

%type<str> fichId id tagname LOAD SHOW LIST EXIT HELP QLE UNKNOWN Comando ComList Interp atribname END
%type<no>  Idlist DocSelector QueryExp QueryExp2 TagList FilterList Filter
%type<num> Context Context2
%type<pathxml> Tag

%%
Interp		: ComList;

ComList		: Comando { showPrompt(); }
     		| ComList Comando { showPrompt();}
			;

Comando		: LOAD fichId id {xmlFile = NULL; errorOcurred = 0; parseXmlFile($2); 
								if (xmlFile) {
									FileInfo info = createFileInfo($3,$2,xmlFile);
									list = addFile(list, info);
									printf("Ficheiro adicionado com sucesso!\n");
								}
							 }
          	| SHOW id	{ showFile(list,$2); }
          	| LIST		{ listFiles(list); }
          	| EXIT		{ printf("Programa terminado!\n"); YYACCEPT; }	
          	| HELP		{ showHelpMessage(); }
            | QLE DocSelector QueryExp END { printf("DOCS:\n"); list_foreach($2,printStringList); printf("TAGS:\n"); printXpathExpression($3);
											 printFilteredNodesForFile(list,$2,$3); }
			| UNKNOWN
			;

DocSelector : '*' { $$ = NULL; }
			| Idlist { $$ = $1; }
			;

Idlist		: Idlist ',' id { $$ = list_insert_beginning($$,$3); }
			| id { $$ = list_insert_beginning(NULL,$1); }
			;

QueryExp	: PERIOD Context2 QueryExp2  { setDirectChild($3,1); ((XmlPath) $3->data)->slashPrefixNo = $2; $$ = $3; }
            | QueryExp2 { $$ = $1; }
            ;

QueryExp2	: TagList Context2 atribname 	{ XmlPath atribNode = createXmlNode($3,NULL,1,$2);
                                              $$ = addXmlPathNode($1,atribNode); }
            | Context atribname 			{ XmlPath atribNode = createXmlNode($2,NULL,1,$1);
                                              $$ = addXmlPathNode(NULL,atribNode); }
            | TagList  						{ $$ = $1; }
            ;

Context		: Context2		{ $$ = $1; }
            | 				{ $$ = 0; }
            ;

Context2	: SLASH			{ $$ = 1; }
            | DOUBLESLASH   { $$ = 2; }
            ;

TagList		: TagList Context2 Tag	{ $3->slashPrefixNo = $2; $1 = addXmlPathNode($1,$3); $$ = $1;  }
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

Filter		: '[' QueryExp ']' {$$ = $2; }

%%
void showAppLogo(){
	printf(".-..-..-..-..-.     .-.   .-.           .-.   .-.                     .-.\n");
	printf(": `' :: `' :: :     : :.-.: :           : :.-.: :                     : :\n");
	printf("`  ' : .. :: :     : :: :: : .--. .--. : `'.': `-.  .--. ,-.,-. .--. : `-.\n");
	printf(".'  `.: :; :: :__   : `' `' ;' .; :: ..': . `.' .; :' '_.': ,. :'  ..': .. :\n");
	printf(":_;:_;:_;:_;:___.'   `.,`.,' `.__.':_;  :_;:_;`.__.'`.__.':_;:_;`.__.':_;:_;\n");
	showPrompt();
}


void showPrompt(){
	printf("\n>");
}

void showHelpMessage(){
	printf("A aplicação 'XML Workbench' tem disponíveis os seguintes comandos:\n");
    printf(BOLDRED "\tLOAD <path para o documento> id" RESET " — Este comando irá usar o parser desenvolvido no ponto anterior para reconhecer e carregar um documento XML. No fim, deverá ainda criar uma entrada numa estrutura de dados interna em que o identificador id fica associado ao documento reconhecido;\n");
    printf(BOLDRED "\tLIST" RESET " — Mostra no écran a lista de documentos carregados e respectivos ids;\n");
    printf(BOLDRED "\tSHOW id" RESET " — Mostra no écran o documento associado ao identificador id em formato ESIS;\n");
    printf(BOLDRED "\tEXIT" RESET " — Sai do programa;\n");
    printf(BOLDRED "\tHELP" RESET " — Imprime no écran um texto parecido com esta lista de comandos.\n");
    printf(BOLDRED "\tQLE: <DOCS> <XQL> " RESET " — Imprime no écran uma lista dos nós que fazem match com a expressão passada.\n");
	printf("\n");
}

int printStringList(void* s){
	if(s) printf("Item: %s\n",(char*) s);
	return 0;
}

int yyerror(char *s){
	 fprintf(stderr,"%s",s);
}

int main(){
	showAppLogo();
	yyparse();
}  
// int main(){
//  	 yyparse();
//  	 return 0;
// }



