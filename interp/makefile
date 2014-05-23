all: interp tok main

main: main.o y.tab.o lex.yy.o
	gcc -o main main.o y.tab.o lex.yy.o -ll

main.o: main.c
	gcc -c main.c

tok: tokenizer.o lex.yy.o
	gcc -o tok tokenizer.o lex.yy.o -ll

tokenizer.o: tokenizer.c
	gcc -c tokenizer.c 

interp : y.tab.o lex.yy.o
	gcc -o interp y.tab.o lex.yy.o -ll

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h y.tab.c : interp.y
	yacc -d interp.y

lex.yy.c : interp.l
	flex interp.l
