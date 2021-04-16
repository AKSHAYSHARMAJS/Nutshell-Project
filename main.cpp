#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "node.h"
#include <string>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <dirent.h>

void processCommand();
extern int cmd_number;
extern char* varTbl[128][100];
extern int row, col, wild;
extern struct LL *list;
extern char* wildcard[100];
int filedesc;
extern char** environ;
int saved_stdout;


int getCommand() {

	if (yyparse())
  {
		//TODO understand_errors();
		return 0;
	}
	else
  {
		return 1;
	}
}


void redirectIO_greater(char* f) {
	filedesc = open(f, O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	saved_stdout = dup(1);
	dup2(filedesc, 1);
	close(filedesc);
}


void runcd()
{
	if(col >= 3)
	{
		if (strcmp(varTbl[row-1][col-2], "greater") == 0) {
			redirectIO_greater(varTbl[row-1][col-1]);
			int ch = chdir(varTbl[row-1][col-3]);
			if (ch < 0)
			{
				printf("Directory not found\n");
			}
			dup2(saved_stdout, 1);
		}
		else if (strcmp(varTbl[row-1][col-2], "less") == 0)
		{
			perror("Cannot read from file with command cd\n");
			return;
		}
	}
	else
	{
		int ch = chdir(varTbl[row - 1][col - 1]);
		if(ch != 0)
		{
			printf("Directory not found\n");
		}
	}

}


void runalias()
{
	push_LL(list, varTbl[row-1][col-2], varTbl[row-1][col-1]);
}


void backgroundProcess()
 {
	int child;
	if ((child = fork()) == 0)
	{
		processCommand();
	}
	else
	{
		if ((varTbl[row-1][col-1], "&"))
		{
			wait(&child);
		}
	}
}


void runsetenv ()
{
	if (strcmp(varTbl[row-1][col-1], "&") == 0)
	{
		varTbl[row-1][col-1] = "-";
		col--;
		backgroundProcess();
	}
	else if (strcmp(varTbl[row-1][col-2], "greater") == 0)
	{
		redirectIO_greater(varTbl[row-1][col-1]);
		setenv(varTbl[row-1][col-4], varTbl[row-1][col-3], 1);
		dup2(saved_stdout, 1);
	}
	else if (strcmp(varTbl[row-1][col-2], "less") == 0)
	{
		printf("Cannot read from file with command setenv\n");
	}
	else {
		setenv(varTbl[row-1][col-2], varTbl[row-1][col-1], 1);
	}
}


void rununsetenv ()
{
	if (col >= 2)
	{
		if (strcmp(varTbl[row-1][col-1], "&") == 0)
		{
			varTbl[row-1][col-1] = "-";
			col--;
			backgroundProcess();
		}
		else if (strcmp(varTbl[row-1][col-2], "greater") == 0)
		{
			redirectIO_greater(varTbl[row-1][col-1]);
			if(strcmp(varTbl[row-1][col-3],"PATH") == 0 || strcmp(varTbl[row-1][col-3],"HOME") == 0)
				{
					printf("Cannot unset environment variable: %s\n", varTbl[row-1][col-3]);
					return;
				}
			unsetenv(varTbl[row-1][col-3]);
			dup2(saved_stdout, 1);
		}
		else if (strcmp(varTbl[row-1][col-2], "less") == 0)
		{
			printf("Cannot read from file with command unsetenv\n");
			return;
		}
	}
	else
	{
		if(strcmp(varTbl[row-1][col-1],"PATH") == 0 || strcmp(varTbl[row-1][col-1],"HOME") == 0)
			{
				printf("Cannot unset environment variable: %s\n", varTbl[row-1][col-1]);
				return;
			}
			unsetenv(varTbl[row-1][col-1]);
	}

}


int redirectIO_less () {
	int mypipe[2]; //pipe with two ends, read and write
	pid_t p;
	int mutex, wpid;
	pipe(mypipe); //creates pipe
	p = fork();
	if (p < 0) {
		printf("fork failed");
	}
	else if (p == 0) {
		int filedesc = open(varTbl[row-1][col-1], O_RDONLY);
		dup2(filedesc, STDIN_FILENO);
		close(filedesc);
		char dest[100];
		strcpy(dest, getenv("PWD"));
		strcat(dest, "/");
		strcat(dest, varTbl[row-1][col-1]);
		execl(dest, varTbl[row-1][col-1], 0);
	}
	else {
		while ((wpid = wait(&mutex)) > 0) {
			//parent process waits until child exits
		}
	}
	return 0;
}


void runprintenv()
{
	if (col >= 2)
	{
		if (strcmp(varTbl[row-1][col-2], "greater") == 0)
		{
			redirectIO_greater(varTbl[row-1][col-1]);
		}
		else if (strcmp(varTbl[row-1][col-2], "less") == 0)
		{
			printf("Cannot read from file with command printenv");
			return;
		}
	}

		int k = 0;
		while (environ[k]) {
			printf("%s\n", environ[k++]);
		}
		dup2(saved_stdout, 1);
}


void runls()
{
	DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if(d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				printf("%s\n", dir->d_name);
			}
			closedir(d);
		}
}

void runls_dir()
{
		if (col >= 2)
		{
			if (strcmp(varTbl[row-1][col-2], "greater") == 0)
			{
				redirectIO_greater(varTbl[row-1][col-1]);
				wild--;
				while(wild >= 0)
				{
					printf("%s\n", wildcard[wild]);
					wild--;
				}
				dup2(saved_stdout, 1);
			}
			else if (strcmp(varTbl[row-1][col-2], "less") == 0)
			{
				printf("Can't read from file in ls");
			}
	}
	else
	{
			wild--;
			while(wild >= 0)
			{
				printf("%s\n", wildcard[wild]);
				wild--;
			}
	}
}


void processCommand()
{
  switch (cmd_number) {
  	case 1: //bye
					printf("BYE!!\n");
					exit(0);
					break;
		case 2:// only cd
					chdir(getenv("HOME"));
					break;
		case 3:// cd with parameters
					runcd();
					break;
		case 4://alias
					runalias();
					break;
		case 5://setenv
					runsetenv();
					break;
		case 6://unsetenv
					rununsetenv();
					break;
		case 7://printenv
					runprintenv();
					break;
		case 8:
					redirectIO_less();
					break;
		case 9:
					runls();
					break;
		case 10:
					runls_dir();
					break;
  }
	cmd_number = -1;

}


int main(int argc, char* argv[], char **envp)
{
	list = create_LL();
	char cwd[PATH_MAX];
	while(1) {
		getcwd(cwd, sizeof(cwd));
		printf("[%s]>> ", cwd);
    		if(getCommand())
        	processCommand();
	}
	return 0;
}
