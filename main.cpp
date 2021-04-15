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
#include <fcntl.h>
#include <dirent.h>

void processCommand();
extern int cmd_number;
extern char* varTbl[128][100];
extern int row, col;
extern struct LL *list;

extern char** environ;

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
	int filedesc = open(f, O_RDWR | O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
	if (filedesc != -1) {
		dup2(filedesc, 2);
	}
	else {
		printf("%s",f);
	}
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
		}
		else if (strcmp(varTbl[row-1][col-2], "less") == 0)
		{
			perror("Cannot read from file with command cd");
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
	}
	else if (strcmp(varTbl[row-1][col-2], "less"))
	{
		printf("Cannot read from file with command setenv");
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
			unsetenv(varTbl[row-1][col-3]);
		}
		else if (strcmp(varTbl[row-1][col-2], "less") == 0)
		{
			printf("Cannot read from file with command unsetenv");
		}
	}
	else
	{
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
		}
	}
	else
	{
		int k = 0;
		while (environ[k]) {
			printf("%s\n", environ[k++]);
		}
	}
}


void processCommand()
{
  switch (cmd_number) {
  	case 1: //bye
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
