all: lexxer.l parser.y main.cpp
	bison -d parser.y
	flex lexxer.l
	g++ main.cpp parser.tab.c node.cpp lex.yy.c -lreadline -o main
