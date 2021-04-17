# THE NUTSHELL TERM PROJECT
 
# Description
The objective of this Project is to design a command interpreter for Korn shell-like command language in C using Lex and Yacc. The code is contained within the main.cpp, node.h, node.cpp, lexxer.l and parser.y files.


# Features Not Working

(1) Using Pipes with Non-built-in Commands

(2) Using both Pipes and I/O Redirection, combined, with Non-built-in Commands


# Features Working

(1) Built-in Commands

(2) Non-built-in Commands

(3) Running Non-built-in Commands in Background

(4) Redirecting I/O with Non-built-in Commands (on some commands like ls, head)

(5) Environment Variable Expansion

(6) Alias Expansion

(7) Wildcard Matching

(8) Shell Robustness

(9) Error Handling and Reporting

(10) Tilde Expansion 

(11) File Name Completion 


# Features

(1) This shell identifies the word or meta in the input command.

(2) It provides aliasing support :-
		->	alias - (without arguments) The alias command with no arguments lists all current key-value aliases.
		->	alias name word - (with arguments) This alias command adds a new alias to the shell.
		->	unalias name - The unalias command is used to remove the alias for name from the alias list.


(3) It provides the cd (change directory) support :-
		-> cd - (withoud arguments) Change the working directory to HOME path.
		-> cd name - Change the working directory to path of "name" directory.
		-> cd .. - Change the directory to parent of working directory.

(4) Other built-in command (touch, head, tail).

(5) Provides bye command to end the shell.

(6) IO redirection: stdout, stderr, and stdin can all be redirected.

(7) Environment variable expansion - This shell reads all the characters inside command line form $.

(8) Wildcard matching with the '*' and '?' characters.

(9) Shell can run an executable file when provided with the abosule path

 (10) tokens that are recognized by parser are : BYE ENDF CD ALIAS QUOTE UNALIAS SETENV PRINTENV UNSETENV LESS GREATER STAR AND QUESTION DOLLAR OCURL CCURL LS PRINT PWD TILDE TOUCH HEAD TAIL CAT WC ESC MKDIR RM DATE WORD ARG

# EXTRA CREDIT

(1) Tilde Expansion  
~name will replace with user's name home directory.
~name will replace by the home directory of current user, when it is not followed by a user.

(2) File Name Completion
Shell completes the partially-typed username.
Shell will do the expansion when ESC character is typed and **press enter**.
It completes the word which begins with tilde with a user name if user name exists else it just give error.



# Declarations

		-> Identification of word and meta (~,",*, ?, $, {,}, >, <)
        -> implemented alias using linked list as to store aliases related functions
		-> commands (date, rm, mkdir, pwd, echo, touch, head, tail)
        -> Environment Variable Expansion
        -> detection of arguments (working with ls, head, tail)
        -> File Name Completion (Extra Credit)

		-> Alias loop detection and expansion using recursion
		-> redirection of IO to a particular file (ls, head)
		-> commands (ls, wc, cd, setenv, printenv, alias, unalias, unsetenv, bye, )
        -> Wildcard Matching
        -> Shell Robustness
        -> Error Handling and Reporting
        -> Tilde Expansion (Extra Credit)




# Code Structure

(1) node.h : Defines the linked list that store the alias to value mapping.

(2) node.cpp : Contains the functions declared in node.h

(3) lexxer.l : reads the input and tokenize them.

(4) parser.y : analyze the possible grammer

(5) main.cpp : contains main function that initiates the command



# TO RUN SHELL 
A Makefile is included with our shell project submission. To run our shell, simply run **'make'** and then **'./main'**
		 
