all: xml tok

tok: tokenizer.o lex.yy.o
	gcc -o tok tokenizer.o lex.yy.o -ll

tokenizer.o: tokenizer.c
	gcc -c tokenizer.c 

xml : y.tab.o lex.yy.o
	gcc -o xml y.tab.o lex.yy.o -ll

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h y.tab.c : xml.y
	yacc -d xml.y

lex.yy.c : xml.l
	flex xml.l
