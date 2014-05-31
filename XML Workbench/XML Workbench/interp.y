%{
#include <stdio.h>
#include "FileInfo.h"
#include "global.h"

#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

NODE* list=NULL;
extern int parseXmlFile(char* path);

NodePtr xmlFile=NULL;

void showHelpMessage();
void showPrompt();
%}

%token LOAD SHOW LIST EXIT HELP UNKNOWN
%token fichId id
%start Interp

%union{
	char *str;
}

%type<str> fichId id LOAD SHOW LIST EXIT HELP UNKNOWN Comando ComList Interp

%%
Interp		: ComList;

ComList		: Comando { showPrompt(); }
     		| ComList Comando { showPrompt();}
			;

Comando		: LOAD fichId id {xmlFile = NULL; parseXmlFile($2); 
								if (xmlFile) {
									FileInfo info = createFileInfo($3,$2,xmlFile);
									list = addFile(list, info);
								}
							 }
          	| SHOW id	{ showFile(list,$2); }
          	| LIST		{ listFiles(list); }
          	| EXIT		{ printf("Programa terminado!\n"); YYACCEPT; }	
          	| HELP		{ showHelpMessage(); }
			| UNKNOWN	
			;

%%

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

int yyerror(char *s){
	 fprintf(stderr,"%s",s);
}

int main(){
	showPrompt();
	yyparse();
}  
// int main(){
//  	 yyparse();
//  	 return 0;
// }



