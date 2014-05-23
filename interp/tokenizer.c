#include <stdio.h>
#include "y.tab.h"

extern int yylex();

int main(){

	int token;

	while((token=yylex())!=0){
	
		switch(token){
			case LOAD : printf("LOAD\n");
				       break;

			case SHOW : printf("SHOW\n");
				       break;

			case LIST : printf("LIST\n");
				       break;

			case EXIT : printf("EXIT\n");
				       break;

			case HELP : printf("HELP\n");
				       break;

			case id : printf("id\n");
				       break;

			case fichId : printf("fichId\n");
				       break;

			default : printf("%d\n",token);
		}
	}
}
