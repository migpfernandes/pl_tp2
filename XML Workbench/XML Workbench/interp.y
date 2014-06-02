%{
#include <stdio.h>
#include "FileInfo.h"
#include "global.h"
#include "list.h"

#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

NODE* list=NULL;
extern int parseXmlFile(char* path);

NodePtr xmlFile=NULL;

void showHelpMessage();
void showPrompt();
int printStringList(void *s);
%}

%token LOAD SHOW LIST EXIT HELP QLE UNKNOWN END
%token fichId id tagname
%start Interp

%union{
	char *str;
	NODE* no;
}

%type<str> fichId id tagname LOAD SHOW LIST EXIT HELP QLE UNKNOWN Comando ComList Interp
%type<no> Tagchain Idlist DocSelector Queryexp

%%
Interp		: ComList;

ComList		: Comando { showPrompt(); }
     		| ComList Comando { showPrompt();}
			;

Comando		: LOAD fichId id {xmlFile = NULL; parseXmlFile($2); 
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
			| QLE DocSelector Queryexp END { printf("DOCS:\n"); list_foreach($2,printStringList); printf("TAGS:\n"); list_foreach($3,printStringList); } 
			| UNKNOWN	
			;

DocSelector : '*' { $$ = NULL; }
			| Idlist { $$ = $1; }
			;

Idlist		: Idlist ',' id { $$ = list_insert_beginning($$,$3); }
			| id { $$ = list_insert_beginning(NULL,$1); }
			;

Queryexp	: Tagchain  {$$ = $1; }
			;

Tagchain	: Tagchain tagname {$$ = list_insert_beginning($1,$2); } 
			| tagname {$$ = list_insert_beginning(NULL,$1); }
			;

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



