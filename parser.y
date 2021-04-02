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
const char* varTbl[128][100];
int varTbl_row = 0;
int varTbl_col = 0;
const char* temp_string;
%}

%union {
	char* string;
	int num;
}

%token BYE ENDF CD
%token <string> WORD META

%%

commandline:
  | commandline command ;

command:
  | bye | cd | word | meta;

params:
		WORD {
			temp_string = $1;
		};

bye:
  ENDF { exit(0);};
  | BYE { cmd_number = 1;};

cd:
	CD {
			cmd_number = 2;
		};
	| CD params {
			cmd_number = 3;
			varTbl_col = 0;
			varTbl[varTbl_row][varTbl_col] = temp_string;
			varTbl_col++;
			varTbl_row++;
	};

word:
  WORD {printf("Detected a word : %s \n", $1);};

meta:
	META {printf("Detected a meta character : %s \n", $1);};
  %%
