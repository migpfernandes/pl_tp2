#include <stdio.h>
#include "y.tab.h"

extern int yylex();

int main(){

	int token;

	while((token=yylex())!=0){
	
		switch(token){
			case name : printf("NAME\n");
				       break;

			case SLASH : printf("SLASH\n");
				       break;

			case atrib : printf("ATRIB\n");
				       break;

			case END : printf("END\n");
				       break;

			case '[' : printf("[\n");
					   break;

			case ']' : printf("]\n");
					   break;

			default : printf("%d\n",token);
		}
	}
}
