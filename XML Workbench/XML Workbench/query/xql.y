%{
#include <stdio.h>

%}

%token name atrib END SLASH ERROR
%start Xql

%union {
	char* str;
}

%type<str> name atrib END

%%
Xql			: Run  { printf("Passou no Xql.\n"); };

Run			: Run QueryExp END { printf("Passou no Xql1.\n"); }
			| QueryExp END  { printf("Passou no Xql2.\n"); }
			;



QueryExp	: TagList SLASH  atrib
			| atrib
			| TagList
			;

TagList		: TagList SLASH Tag
			| Tag
			| SLASH Tag
			;

Tag			: name FilterList { printf("Passou na Tag\n"); }
			| '*' FilterList
			;

FilterList	: FilterList Filter
			| 
			;

Filter		: '[' QueryExp ']' {printf("Passou no filter.\n"); }

%%

int yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}

int main(){
	yyparse();
	return 1;
}
