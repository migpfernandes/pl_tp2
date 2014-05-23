%{
#include <stdio.h>
%}

%token LOAD SHOW LIST EXIT HELP
%token fichId id

%%
Interp		: ComList;

ComList		: Comando
     		| ComList Comando
			;

Comando		: LOAD fichId id
          	| SHOW id
          	| LIST
          	| EXIT
          	| HELP
			;

%%

int yyerror(char *s){
	 fprintf(stderr,"%s",s);
}

int teste(){
	yyparse();
}  
// int main(){
//  	 yyparse();
//  	 return 0;
// }



