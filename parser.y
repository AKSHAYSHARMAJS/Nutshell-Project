%{

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "node.h"
#include <string>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>

int yylex();

int yyparse();

void yyerror(char *s){
	fprintf(stderr, "error: %s\n",s);
}

int cmd_number = -1;
char* varTbl[128][100];
char* wildcard[100];
int wild = 0;
int row = 0;
int col = 0;
char* temp_string = "temp";
char* temp_string2 = "temp";
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

%token BYE ENDF CD ALIAS QUOTE UNALIAS SETENV PRINTENV UNSETENV LESS GREATER STAR AND QUESTION DOLLAR OCURL CCURL PIPING LS PRINT PWD TILDE
%token <string> WORD

%%

cmdline:
  | cmdline cmd ;

cmd:
  | bye | cd | alias | unalias | setenv | printenv | unsetenv | piping | redirectIO | read_from_io | ls | echo | pwd | envexpand | word ;


envexpand:
		DOLLAR OCURL WORD CCURL {
			 	printf("%s\n",getenv($3));
			}
			|


params:
		CD {
			temp_string = "cd";
		}
		| UNALIAS {
			temp_string = "unalias";
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
		| LS {
			temp_string = "ls";
		}
		| PRINT {
			temp_string = "echo";
		}
		| WORD {
			temp_string = $1;
		}
		| params WORD {
			char buffer[100];
			strcpy(buffer, temp_string);
			strcat(buffer, " ");
			strcat(buffer, $2);
			temp_string = buffer;
		}

		| params DOLLAR OCURL WORD CCURL  {
			char buffer[100];
			strcpy(buffer, temp_string);
			strcat(buffer, " ");
			strcat(buffer, getenv($4));
			temp_string = buffer;
		}
		| STAR WORD {
			wild = 0;
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
					int outlength = strlen(stringout) -1;
					int k;
					for (k = length - 1; k >= 0; k--)
					 {
						if (stringout[outlength] != stringin[k])
						{
							matching = 0;
							break;
						}
						outlength--;
					}
					if (matching == 1)
					{
						temp_string = stringout;
						wildcard[wild] = temp_string;
						wild++;

					}
				}
			closedir(d);
			}
		}
		| WORD STAR {
			wild = 0;
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
					int k;
					for (k = 0; k < length; k++)
					{
						if (stringout[k] != stringin[k])
						{
							matching = 0;
							break;
						}
					}
					if (matching == 1)
					{
						temp_string = stringout;
						wildcard[wild] = temp_string;
						wild++;
					}
				}
			closedir(d);
			}
		}
		| QUESTION WORD {
			wild = 0;
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
					int outlength = strlen(stringout) - 1;
					int k;
					for (k = length - 1; k >= 0; k--)
					{
						if (stringout[outlength] != stringin[k])
						{
							matching = 0;
							break;
						}
						outlength--;
					}
					if (matching == 1 && outlength == 1)
					{
						temp_string = stringout;
						wildcard[wild] = temp_string;
						wild++;
					}
				}
			closedir(d);
			}
		}
		| WORD QUESTION {
			wild = 0;
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
					int k;
					for (k = 0; k < length; k++)
					{
						if (stringout[k] != stringin[k])
						{
							matching = 0;
							break;
						}
					}
					if (matching == 1)
					{
						temp_string = stringout;
						wildcard[wild] = temp_string;
						wild++;
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
	| CD TILDE {
		cmd_number = 2;
	}
	| CD TILDE WORD{
		struct passwd *pw;
		if((pw = getpwnam($3)) == NULL)
    {
          fprintf(stderr, "unknown user %s\n", $3);
    }
		else
		{
			cmd_number = 3;
			col = 0;
			varTbl[row][col] = pw->pw_dir;
			col++;
			row++;
		}

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


ls:
 		LS {
				cmd_number = 9;
			}
			| LS PIPING {
				cmd_number = 9;
			}
			| LS params{
				col = 0;
				cmd_number = 10;
				varTbl[row][col] = temp_string;
				col++;
				row++;
			}
			| LS params redirectIO {
				col = 0;
				cmd_number = 10;
				varTbl[row][col] = temp_string;
				col++;
				varTbl[row][col] = io;
				col++;
				varTbl[row][col] = temp_string2;
				col++;
				row++;
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


echo:
		PRINT WORD {
			printf("%s", $2);
		}
		| PRINT QUOTE WORD QUOTE{
			printf("%s", $3);
		}
		| PRINT QUOTE params QUOTE {
			printf("%s", temp_string);
		}


pwd:
	PWD{
		printf("%s\n",getenv("PWD"));
	}


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
