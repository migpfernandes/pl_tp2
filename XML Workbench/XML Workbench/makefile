# all: xml tok
# all: interp tok main

# all: xml interp
all: interp main

# tok: tokenizer.o lex.yy.o
#	gcc -o tok tokenizer.o lex.yy.o -ll

# tokenizer.o: tokenizer.c
#	gcc -c tokenizer.c

main: main.o FileInfo.o list.o xmldata.o 
	gcc -o main list.o FileInfo.o xmldata.o main.o 

main.o : main.c
	gcc -c main.c

interp : y.tab.o lex.yy.o FileInfo.o list.o xmldata.o xml.tab.o lex.xml.o xmlpath.o
	gcc -o interp y.tab.o list.o FileInfo.o xmldata.o lex.yy.o xml.tab.o lex.xml.o xmlpath.o -ll

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h y.tab.c : interp.y
	yacc -d interp.y

lex.yy.c : interp.l
	flex interp.l



# tok: tokenizer.o lex.xml.o
#	gcc -o tok tokenizer.o xmldata.o lex.yy.o xml.tab.o -ll

# tokenizer.o: tokenizer.c
#	gcc -c tokenizer.c

# xml : xml.tab.o lex.xml.o xmldata.o
#	gcc -o xml xml.tab.o lex.xml.o xmldata.o -ll

lex.xml.o : lex.xml.c xml.tab.h
	gcc -c lex.xml.c

xml.tab.o : xml.tab.h xml.tab.c
	gcc -c xml.tab.c

lex.xml.c : xml.l xml.tab.h 
	flex -P xml xml.l

xml.tab.h xml.tab.c : xml.y
	yacc -d -b xml -p xml xml.y

FileInfo.o : FileInfo.c FileInfo.h
	gcc -c FileInfo.c

list.o : list.c list.h
	gcc -c list.c

xmldata.o: xmldata.c xmldata.h
	gcc -c xmldata.c

xmlpath.o: xmlpath.c xmlpath.h
	gcc -c xmlpath.c