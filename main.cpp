#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

extern int cmd_number;

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

void processCommand()
{
  if(cmd_number == 20)
	{
		printf("Bye!!\n");
		exit(0);
	} //check for 'bye' command
}

int main(int argc, char* argv[], char **envp) {

	while(1) {

    		int c = getCommand();
        processCommand();
	}
	return 0;
}
