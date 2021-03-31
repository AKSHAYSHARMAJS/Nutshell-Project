all: lexxer.l parser.y main.cpp
	bison -d parser.y
	flex lexxer.l
	g++ main.cpp parser.tab.c lex.yy.c -o main
