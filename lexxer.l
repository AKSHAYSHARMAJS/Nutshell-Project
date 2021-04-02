%{

#include "parser.tab.h"
%}

%option noyywrap

%%

bye {return BYE;}
cd  {return CD;}
[<>|"\\&] {yylval.string = strdup(yytext);return META;}
[0-9a-zA-Z/\.]+ {yylval.string = strdup(yytext); return WORD; };
[\n] {return -1;}
<<EOF>> {return ENDF;}
[ \t\r]+                          { ; } /* Ignore Whitespace */
.                                 { ; } /* No Match */

%%
