%{
#include "parser.tab.h"
%}

%%

"&&"            { return AND_IF; }
"||"            { return OR_IF; }
";;"            { return DSEMI; }
"<<"            { return DLESS; }
">>"            { return DGREAT; }
"<&"            { return LESSAND; }
">&"            { return GREATAND; }
"<>"            { return LESSGREAT; }
"<<-"           { return DLESSDASH; }
">|"            { return CLOBBER; }
"if"            { return If; }
"then"          { return Then; }
"else"          { return Else; }
"elif"          { return Elif; }
"fi"            { return Fi; }
"do"            { return Do; }
"done"          { return Done; }
"case"          { return Case; }
"esac"          { return Esac; }
"while"         { return While; }
"until"         { return Until; }
"for"           { return For; }
"{"             { return Lbrace; }
"}"             { return Rbrace; }
"!"             { return Bang; }
"in"            { return In; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return NAME; }
[0-9]+          { yylval.str = strdup(yytext); return IO_NUMBER; }
"="             { return ASSIGNMENT_WORD; }
\n              { return NEWLINE; }
[ \t]+          { /* Ignore whitespace */ }
.               { yyerror("Unknown character"); }

%%

int yywrap() {
    return 1;
}