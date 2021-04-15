%{

#include "parser.tab.h"
%}

%option noyywrap

%%

bye {return BYE;}
cd  {return CD;}
alias {return ALIAS;}
unalias {return UNALIAS;}
setenv {return SETENV;}
printenv {return PRINTENV;}
unsetenv {return UNSETENV;}
[\"] {return QUOTE;}
[\<] {return LESS;}
[\>] {return GREATER;}
[\*] {return STAR;}
[\&] {return AND;}
[\?] {return QUESTION;}
[\$] {return DOLLAR;}
[\{] {return OCURL;}
[\}] {return CCURL;}
[\|] {return PIPING;}
[0-9a-zA-Z/\.]+ {yylval.string = strdup(yytext); return WORD; };
[\n] {return -1;}
<<EOF>> {return ENDF;}
[ \t\r]+                          { ; } /* Ignore Whitespace */
.                                 { ; } /* No Match */

%%
