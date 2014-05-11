#include <stdio.h>
#include "y.tab.h"

extern int yylex();

int main(){

	int token;

	while((token=yylex())!=0){
	
		switch(token){
			case SINGLETAGE : printf("SINGLETAGE\n");
				       break;
			case ENDTAGB : printf("ENDTAGB\n");
				       break;

			case id : printf("id\n");
				       break;

			case valor : printf("valor\n");
				       break;
			case '=' : printf("=\n");
				       break;

			case texto : printf("texto\n");
				       break;


			case '<' : printf("<\n");
				       break;

			case '>' : printf(">\n");
				       break;
	
			case '&' : printf("&\n");
				       break;

			case ';' : printf(";\n");
				       break;

			case '$' : printf("$\n");
				       break;

			default : printf("%d\n",token);
		}
	}
}
