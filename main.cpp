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
#include <fstream>
#include <iostream>



void processCommand();
extern int cmd_number;
extern char* varTbl[128][100];
extern int row, col, wild;
extern struct LL *list;
extern char* wildcard[100];
extern char** environ;
extern int filedesc;
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

void runprintenv()
{
	if (col >= 2)
	{
		if (strcmp(varTbl[row-1][col-2], "greater") == 0)
		{
			redirectIO_greater(varTbl[row-1][col-1]);
			int k = 0;
			while (environ[k]) {
				printf("%s\n", environ[k++]);
			}
			dup2(saved_stdout, 1);
		}
		else if (strcmp(varTbl[row-1][col-2], "less") == 0)
		{
			printf("Cannot read from file with command printenv");
			return;
		}
	}
	else{
		int k = 0;
		while (environ[k]) {
			printf("%s\n", environ[k++]);
		}
	}



}


void runls()
{
	DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if(col >= 2)
		{
			if (strcmp(varTbl[row-1][col-2], "greater") == 0)
			{
				redirectIO_greater(varTbl[row-1][col-1]);
				if(d)
				{
					while ((dir = readdir(d)) != NULL)
					{
						printf("%s\n", dir->d_name);
					}
					closedir(d);
				}
				dup2(saved_stdout, 1);
			}
			else if (strcmp(varTbl[row-1][col-2], "less") == 0)
			{
				printf("Can't read from file in ls");
			}
		}
		else{
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					printf("%s\n", dir->d_name);
				}
				closedir(d);
			}
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


void runls_flag()
{
		if(strcmp(varTbl[row-1][col-1],"-l") == 0 || strcmp(varTbl[row-1][col-1],"-lah") == 0 || strcmp(varTbl[row-1][col-1],"-al") == 0)
			{
				DIR *d;
				struct dirent *dir;
				d = opendir(".");
				if(d)
				{
					while ((dir = readdir(d)) != NULL)
					{
							struct stat fileStat;
							if(stat(dir->d_name, &fileStat) < 0)
							{
									printf("file not exits");
									return;
							}
							printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
							printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
							printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
							printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
							printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
							printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
							printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
							printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
							printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
							printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
							printf("\t");
							printf("%d %d %d\t", fileStat.st_size, fileStat.st_nlink,fileStat.st_ino);
							printf("%s\n", dir->d_name);
					}
					closedir(d);
				}
			}

		else
		{
				printf("Not a valid flag for ls\n");
				return;
			}

}


void runTouch()
{
	std::ofstream MyFile(varTbl[row-1][col-1]);
}


void run_head()
{
	if(col >= 2 && strcmp(varTbl[row-1][col-2], "greater") == 0)
	{
		redirectIO_greater(varTbl[row-1][col-1]);
		std::string word;
	    std::fstream file;
	    int count = 1;

	    file.open(varTbl[row - 1][col - 3]);
	    int numOfLines=0;

	    while(getline(file, word) && numOfLines < 10){
	        std::cout << word << std::endl;
	        numOfLines++;

	    }
			dup2(saved_stdout, 1);
			close(saved_stdout);

	}
	else
	{
		std::string word;
	    std::fstream file;
	    int count = 1;

	    file.open(varTbl[row - 1][col - 1]);
	    int numOfLines=0;

	    while(getline(file, word) && numOfLines < 10){
	        std::cout << word << std::endl;
	        numOfLines++;
	    }
	}


}

void run_head_arg()
{

	std::string word;
    std::fstream file;
		std::string num = "";
		char arg[1000];
		strcpy(arg, varTbl[row-1][col-2]);
		for(int i = 1; arg[i] != '\0'; i++)
		{
			num += arg[i];
		}
    int n = stoi(num);				// Add n as first n number of lines
    file.open(varTbl[row - 1][col - 1]);
    int numOfLines=0;

    while(getline(file, word) && numOfLines < n){
        std::cout << word << std::endl;
        numOfLines++;
    }
}

void run_tail()
{

   std::ifstream myfile(varTbl[row - 1][col - 1]);
   std::string line, buffer[5];
   const size_t size = sizeof buffer / sizeof *buffer;
   size_t i = 0;
   while ( getline(myfile, line) )
   {
      buffer[i] = line;
      if ( ++i >= size )
      {
         i = 0;
      }
   }

   for ( size_t j = 0; j < size; ++j )
   {
      std::cout << buffer[i] << "\n";
      if ( ++i >= size )
      {
         i = 0;
      }
   }
}

void run_tail_arg()
{
	std::string num = "";
	char arg[1000];
	strcpy(arg, varTbl[row-1][col-2]);
	for(int i = 1; arg[i] != '\0'; i++)
	{
		num += arg[i];
	}
	int n = stoi(num);					//Add n as last n number of lines
   std::ifstream myfile(varTbl[row - 1][col - 1]);
   std::string line, buffer[n];
   const size_t size = sizeof buffer / sizeof *buffer;
   size_t i = 0;
   while ( getline(myfile, line) )
   {
      buffer[i] = line;
      if ( ++i >= size )
      {
         i = 0;
      }
   }

   for ( size_t j = 0; j < size; ++j )
   {
      std::cout << buffer[i] << "\n";
      if ( ++i >= size )
      {
         i = 0;
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
		case 9:
					runls();
					break;
		case 10:
					runls_dir();
					break;
		case 11:
					runls_flag();
					break;
		case 12:
					runTouch();
					break;
		case 13:
					run_head();
					break;
		case 14:
					run_head_arg();
					break;
		case 15:
					run_tail();
					break;
		case 16:
					run_tail_arg();
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
