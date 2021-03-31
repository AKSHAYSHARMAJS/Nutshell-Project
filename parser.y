%{

#include <stdio.h>
#include <stdlib.h>
#include <string>

int yylex();

int yyparse();

void yyerror(const char *s){
	fprintf(stderr, "error: %s\n",s);
}
int cmd_number = -1;


%}

%union {
	char* string;
	int num;
}

%token BYE ENDF
%token <string> WORD META

%%



commandline:
  | commandline command;

command:
  | bye | word | meta;

 bye:
  ENDF { exit(0);};
  | BYE {
  		cmd_number = 20;
  	};

word:
  WORD {printf("Detected a word : %s \n", $1);};

meta:
	META {printf("Detected a meta character : %s \n", $1);};
  %%
