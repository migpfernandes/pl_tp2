# all: xml tok

all: xml interp


# tok: tokenizer.o lex.xml.o
#	gcc -o tok tokenizer.o xmldata.o lex.yy.o xml.tab.o -ll

# tokenizer.o: tokenizer.c
#	gcc -c tokenizer.c

xml : xml.tab.o lex.xml.o xmldata.o
	gcc -o xml xml.tab.o lex.xml.o xmldata.o -ll

lex.xml.o : lex.xml.c xml.tab.h
	gcc -c lex.xml.c

xml.tab.o : xml.tab.h xml.tab.c
	gcc -c xml.tab.c

lex.xml.c : xml.l xml.tab.h 
	flex -P xml xml.l

xml.tab.h xml.tab.c : xml.y
	yacc -d -b xml -p xml xml.y

xmldata.o: xmldata.c xmldata.h
	gcc -c xmldata.c







all: interp tok main

main: main.o y.tab.o lex.yy.o
	gcc -o main main.o y.tab.o lex.yy.o -ll

main.o: main.c
	gcc -c main.c

tok: tokenizer.o lex.yy.o
	gcc -o tok tokenizer.o lex.yy.o -ll

tokenizer.o: tokenizer.c
	gcc -c tokenizer.c 

interp : y.tab.o lex.yy.o FileInfo.o list.o xmldata.o
	gcc -o interp y.tab.o list.o FileInfo.o xmldata.o lex.yy.o -ll

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h y.tab.c : interp.y
	yacc -d interp.y

lex.yy.c : interp.l
	flex interp.l

FileInfo.o : FileInfo.c FileInfo.h
	gcc -c FileInfo.c

list.o : list.c list.h
	gcc -c list.c

xmldata.o : xmldata.c xmldata.h
	gcc -c xmldata.c
