%{

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <string>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>

int yylex();

int yyparse();

void yyerror(const char *s){
	fprintf(stderr, "error: %s\n",s);
}

int cmd_number = -1;
char* varTbl[128][100];
int row = 0;
int col = 0;
char* temp_string;
LL *list;

%}

%code requires {
#include "node.h"
}

%union {
	char* string;
	int num;
}

%token BYE ENDF CD ALIAS QUOTE UNALIAS
%token <string> WORD META

%%

commandline:
  | commandline command ;

command:
  | bye | cd | alias | unalias | word | meta ;


params:
		CD {
			temp_string = "cd";
		}
		| WORD {
			temp_string = $1;
		}
		| params WORD {
			strcat(temp_string, " ");
			strcat(temp_string, $2);
		};


bye:
  ENDF { exit(0);}
  | BYE { cmd_number = 1;}


cd:
	CD {
			cmd_number = 2;
		}
	| CD params {
			cmd_number = 3;
			col = 0;
			varTbl[row][col] = temp_string;
			col++;
			row++;
	}
	| CD QUOTE params QUOTE{
		cmd_number = 3;
		col = 0;
		varTbl[row][col] = temp_string;
		col++;
		row++;
	}


alias:
		 ALIAS WORD params {
			cmd_number = 4;
			char *name = $2;
			char *value = temp_string;
			varTbl[row][col] = name;
			col += 1;
			varTbl[row][col] = value;
			col += 1;
			row += 1;
		}
		| ALIAS WORD CD {
			char *name = $2;
			char *value = "cd";
			push_LL(list, name, value);
		}
		| ALIAS WORD QUOTE params QUOTE {
			char *name = $2;
			char *value = temp_string;
			push_LL(list, name, value);
		}
		| ALIAS {
			print_LL(list);
		};


unalias:
			UNALIAS WORD{
			char *name = $2;
			remove_node(list, name);
};


word:
	WORD {
		char *expand = command_expand(list, $1);
		cmd_number = 20;
		if(strcmp("Command not found", expand) == 0)
		{
			printf("%s : Command not found", $1);
		}
		else
		{

			p = fork();
			if (p < 0)
			{
				printf("fork failed");
			}
			else if (p == 0)
			{
				FILE *f;
				f = fopen("cmdvalue.txt", "w");
				fprintf(f, "%s\n", expand);
				fclose(f);
				f = fopen("cmdvalue.txt", "r");
				int filedesc = fileno(f);
				dup2(filedesc, fileno(stdin));
				fclose(f);
				char dest[100];
				strcpy(dest, getenv("PWD"));
				strcat(dest, "/");
				strcat(dest, "cmdvalue.txt");
				execl(dest, "cmdvalue.txt", 0);
			}
			else
			{
				while ((wpid = wait(&mutex)) > 0)
				{
					//parent process waits until child exits
				}
			}
		}
		printf("\n");
};

meta:
	META {printf("Detected a meta character : %s \n", $1);}
  %%
