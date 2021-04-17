%{

#include "parser.tab.h"
#include "node.h"
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
ls {return LS;}
echo {return PRINT;}
pwd {return PWD;}
touch {return TOUCH;}
head { return HEAD;}
tail { return TAIL;}
cat {return CAT;}
wc {return WC;}
[\~] {return TILDE;}
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
[0-9a-zA-Z/\-\:\.]+ {
                        yylval.string = strdup(yytext);

                          if(yytext[0] == '-')
                              return ARG;
                          else
                            return WORD;

                    };
[\n] {return -1;}
<<EOF>> {return ENDF;}
[ \t\r]+                          { ; } /* Ignore Whitespace */
[^[] {return ESC;}
.                                 { ; } /* No Match */

%%
