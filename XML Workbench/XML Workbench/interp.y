%{
#include <stdio.h>
#include "FileInfo.h"

NODE* list=NULL;
extern int parseXmlFile(char* path);
%}



%token LOAD SHOW LIST EXIT HELP
%token fichId id
%start Interp

%union{
	char *str;
}

%type<str> fichId id LOAD SHOW LIST EXIT HELP Comando ComList Interp

%%
Interp		: ComList;

ComList		: Comando
     		| ComList Comando
			;

Comando		: LOAD fichId id { NodePtr fileContent = (NodePtr) parseXmlFile($1); 
								if (fileContent) {
									FileInfo info = createFileInfo($3,$1,fileContent);
									list = addFile(list, info);
								} 
							 }
          	| SHOW id	{ showFile(list,$2); }
          	| LIST		{ listFiles(list); }
          	| EXIT		
          	| HELP
			;

%%

int yyerror(char *s){
	 fprintf(stderr,"%s",s);
}

int main(){
	yyparse();
}  
// int main(){
//  	 yyparse();
//  	 return 0;
// }



