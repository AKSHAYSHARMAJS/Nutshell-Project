#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>

extern int cmd_number;
extern const char* varTbl[128][100];
extern int varTbl_row, varTbl_col;

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

void runcd()
{
	int ch = chdir(varTbl[varTbl_row - 1][varTbl_col - 1]);
	if(ch != 0)
	{
		printf("Directory not found\n");
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
		case 3:// cd with argument
					runcd();
					break;
  }
	cmd_number = -1;

}

int main(int argc, char* argv[], char **envp) {
	char cwd[PATH_MAX];
	while(1) {
		getcwd(cwd, sizeof(cwd));
		printf("[%s]>> ", cwd);
    		if(getCommand())
        	processCommand();
	}
	return 0;
}
