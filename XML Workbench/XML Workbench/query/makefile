all: xql tok

tok : tokenizer.o y.tab.o lex.yy.o
	gcc -o tok y.tab.o lex.yy.o tokenizer.o -ll

tokenizer.o : tokenizer.c
	gcc -c tokenizer.c

xql : y.tab.o lex.yy.o list.o xmldata.o xmlpath.o 
	gcc -o xql y.tab.o lex.yy.o list.o xmldata.o xmlpath.o -ll

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

lex.yy.c : xql.l y.tab.h 
	flex xql.l

y.tab.h y.tab.c : xql.y
	yacc -d xql.y

list.o : list.c list.h
	gcc -c list.c

xmldata.o : xmldata.c xmldata.h
	gcc -c xmldata.c

xmlpath.o : xmlpath.c xmlpath.h
	gcc -c xmlpath.c

