%{

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <string>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int yylex();

int yyparse();

void yyerror(char *s){
	fprintf(stderr, "error: %s\n",s);
}

int cmd_number = -1;
char* varTbl[128][100];
int row = 0;
int col = 0;
char* temp_string;
char* temp_string2;
char* io = "";
LL *list;

%}

%code requires {
#include "node.h"
}

%union {
	char* string;
	int num;
}

%token BYE ENDF CD ALIAS QUOTE UNALIAS SETENV PRINTENV UNSETENV LESS GREATER STAR AND QUESTION DOLLAR OCURL CCURL PIPING
%token <string> WORD

%%

cmdline:
  | cmdline cmd ;

cmd:
  | bye | cd | alias | unalias | setenv | printenv | unsetenv | piping | redirectIO | read_from_io | word ;


params:
		CD {
			temp_string = "cd";
		}
		| UNALIAS {
			temp_string = "unalias";
		}
		| WORD {
			temp_string = $1;
		}
		| params WORD {
			strcat(temp_string, " ");
			strcat(temp_string, $2);
		}
		|	SETENV {
			temp_string = "setenv";
		}
		| UNSETENV {
			temp_string = "unsetenv";
		}
		| PRINTENV {
			temp_string = "printenv";
		}
		/*| LS {
			temp_string = "ls";
		}*/
		| DOLLAR OCURL WORD CCURL {
			temp_string = getenv($3);
			}
		| params DOLLAR OCURL WORD CCURL {
			strcat(temp_string, " ");
			strcat(temp_string, getenv($4));
		}
		| STAR WORD {
			struct dirent *dir;
			DIR *d;
			d = opendir(".");
			int matching, length = strlen($2);
			char *stringin = $2, *stringout;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int outlength = strlen(stringout);
					int i;
					for (i = length; i > 0; i--)
					 {
						if (stringout[outlength] != stringin[i])
						{
							matching = 0;
							break;
						}
						outlength--;
					}
					if (matching == 1)
					{
						temp_string = stringout;
					}
				}
			closedir(d);
			}
		}
		| WORD STAR {
			struct dirent *dir;
			DIR *d;
			d = opendir(".");
			int matching, length = strlen($1);
			char *stringin = $1, *stringout;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int i;
					for (i = 0; i < length; i++)
					{
						if (stringout[i] != stringin[i])
						{
							matching = 0;
							break;
						}
					}
					if (matching == 1)
					{
						temp_string = stringout;
					}
				}
			closedir(d);
			}
		}
		| QUESTION WORD {
		DIR *d;
			struct dirent *dir;
			d = opendir(".");
			int matching, length = strlen($2);
			char *stringout, *stringin = $2;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int outlength = strlen(stringout);
					int i;
					for (i = length; i > 0; i--)
					{
						if (stringout[outlength] != stringin[i])
						{
							matching = 0;
							break;
						}
						outlength--;
					}
					if (matching == 1 && outlength == 1)
					{
						temp_string = stringout;
					}
				}
			closedir(d);
			}
		}
		| WORD QUESTION {
			DIR *d;
			struct dirent *dir;
			d = opendir(".");
			int matching, length = strlen($1);
			char *stringout, *stringin = $1;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int outlength = strlen(stringout);
					if (outlength - length != 1)
					{
						matching = 0;
					}
					int i;
					for (i = 0; i < length; i++)
					{
						if (stringout[i] != stringin[i])
						{
							matching = 0;
							break;
						}
					}
					if (matching == 1)
					{
						temp_string = stringout;
					}
				}
			closedir(d);
			}
		};


bye:
  ENDF { exit(0);}
  | BYE { cmd_number = 1;}

redirectIO:
			GREATER WORD {
			temp_string2 = $2;
			io = "greater";
		}
		|	LESS WORD {
				temp_string2 = $2;
				io = "less";
			};


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
	| CD params redirectIO {
		cmd_number = 3;
		col= 0;
		varTbl[row][col] = temp_string;
		col++;
		varTbl[row][col] = io;
		col++;
		varTbl[row][col] = temp_string2;
		col++;
		row++;
	}

alias:
		 ALIAS WORD params {
			cmd_number = 4;
			char *name = $2;
			char *value = temp_string;
			varTbl[row][col] = name;
			col++;
			varTbl[row][col] = value;
			col++;
			row++;
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


setenv:
		SETENV WORD WORD {
			cmd_number = 5;
			col = 0;
			char* name = $2;
			char* value = $3;
			varTbl[row][col] = name;
			col++;
			varTbl[row][col] = value;
			col++;
			row++;
		}
		| SETENV WORD QUOTE params QUOTE {
			cmd_number = 5;
			col = 0;
			char* name = $2;
			char* value = temp_string;
			varTbl[row][col] = name;
			col++;
			varTbl[row][col] = value;
			col++;
			row++;
		}
	| SETENV WORD WORD AND {
		cmd_number = 5;
		col = 0;
		char* name = $2;
		char* value = $3;
		varTbl[row][col] = name;
		col++;
		varTbl[row][col] = value;
		col++;
		varTbl[row][col] = "&";
		col++;
		row++;
	}
	| SETENV WORD params redirectIO {
		cmd_number = 5;
		col = 0;
		char* name = $2;
		char* value = temp_string;
		char* file = temp_string2;
		varTbl[row][col] = name;
		col++;
		varTbl[row][col] = value;
		col++;
		varTbl[row][col] = io;
		col++;
		varTbl[row][col] = file;
		col++;
		row++;
	};


unsetenv:
			UNSETENV WORD {
				cmd_number = 6;
				col = 0;
				char* name = $2;
				varTbl[row][col] = name;
				col++;
				row++;
			}
			| UNSETENV WORD AND {
				cmd_number = 6;
				col = 0;
				char* name = $2;
				varTbl[row][col] = name;
				col++;
				varTbl[row][col] = "&";
				col++;
				row++;
			}
			| UNSETENV WORD redirectIO {
				cmd_number = 6;
				col = 0;
				varTbl[row][col] = $2;
				col++;
				varTbl[row][col] = io;
				col++;
				varTbl[row][col] = temp_string2;
				col++;
				row++;
			};


printenv:
				PRINTENV {
					cmd_number = 7;
				}
				| PRINTENV PIPING {
					cmd_number = 7;
				}
				| PRINTENV redirectIO {
					cmd_number = 7;
					col = 0;
					varTbl[row][col] = io;
					col++;
					varTbl[row][col] = temp_string2;
					col++;
					row++;
				};

read_from_io:
			LESS params {
				col = 0;
				cmd_number = 8;
				char* file = temp_string;
				io = "less";
				varTbl[row][col] = io;
				col++;
				varTbl[row][col] = file;
				col++;
				col++;
	};


	piping:
		PIPING params{
			cmd_number = 21;
			int mypipe[2]; //pipe with two ends, read and write
			pid_t p;
			int mutex, wpid;
			pipe(mypipe); //creates pipe
			p = fork();
			if (p < 0) {
				printf("fork failed");
			}
			else if (p == 0) {
				FILE *f;
				f = fopen("pipe.txt", "w");
				fprintf(f, "%s\n%s", temp_string, "bye");
				fclose(f);
				f = fopen("pipe.txt", "r");
				int fd = fileno(f);
				dup2(fd, fileno(stdin));
				fclose(f);
				char dest[100];
				strcpy(dest, getenv("PWD"));
				strcat(dest, "/");
				strcat(dest, "pipe.txt");
				execl(dest, "pipe.txt", 0);
			} else {
				while ((wpid = wait(&mutex)) > 0) {
					//
				}
			}
		}
		| PIPING {}
		| PIPING params PIPING{
			cmd_number = 21;
			int mypipe[2]; //pipe with two ends, read and write
			pid_t p;
			int mutex, wpid;
			pipe(mypipe); //creates pipe
			p = fork();
			if (p < 0) {
				printf("fork failed");
			}
			else if (p == 0) {
				FILE *f;
				f = fopen("pipe.txt", "w");
				fprintf(f, "%s\n%s", temp_string, "bye");
				fclose(f);
				f = fopen("pipe.txt", "r");
				int fd = fileno(f);
				dup2(fd, fileno(stdin));
				fclose(f);
				char dest[100];
				strcpy(dest, getenv("PWD"));
				strcat(dest, "/");
				strcat(dest, "pipe.txt");
				execl(dest, "pipe.txt", 0);
			} else {
				while ((wpid = wait(&mutex)) > 0) {
					//
				}
			}
		};


word:
	WORD {
		char *expand = command_expand(list, $1);
		cmd_number = 20;
		if(strcmp("Command not found", expand) == 0)
		{
			printf("%s : command not found", $1);
		}
		else
		{

			int pipe1[2]; //pipe with two ends, read and write
			pid_t p;
			int mutex, wpid;
			pipe(pipe1); //creates pipe
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

  %%
