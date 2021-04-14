%{

#include "parser.tab.h"
%}

%option noyywrap

%%

bye {return BYE;}
cd  {return CD;}
alias {return ALIAS;}
unalias {return UNALIAS;}
[<>|\\&] {yylval.string = strdup(yytext);return META;}
[0-9a-zA-Z/\.]+ {yylval.string = strdup(yytext); return WORD; };
[\"] {return QUOTE;}
[\n] {return -1;}
<<EOF>> {return ENDF;}
[ \t\r]+                          { ; } /* Ignore Whitespace */
.                                 { ; } /* No Match */

%%
