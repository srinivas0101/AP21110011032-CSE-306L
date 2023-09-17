%{
#include <stdio.h>
FILE *outputFile;
%}
%%
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/] {}
"#include<stdio.h>" { fprintf(outputFile, "This is Pre-processor directive: %s", yytext); }
"while"|"if"|"else" { fprintf(outputFile, "\nThis is keyword: %s", yytext); }
"int"|"float" { fprintf(outputFile, "\nThis is keyword: %s", yytext); }
"main()" { fprintf(outputFile, "\nThis is a function: %s", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { fprintf(outputFile, "\nThis is an identifier: %s", yytext); }
"<="|"=="|"="|"++"|"-"|"*"|"+"|"+="|"=+"|"-="|"=-" { fprintf(outputFile, "\nThis is an operator: %s",
yytext); }
")" {}
"["|"]" { fprintf(outputFile, "\nThis is a delimiter: %s", yytext); }
[(){}|,;] { fprintf(outputFile, "\nThis is a delimiter: %s", yytext); }
[\"\'] { fprintf(outputFile, "\nThis is a quote: %s", yytext); }
[0-9]*"."[0-9]+ { fprintf(outputFile, "\nThis is a float: %s", yytext); }
[0-9]+ { fprintf(outputFile, "\nThis is an integer: %s", yytext); }
. { fprintf(outputFile, "\nUnrecognized character: %s", yytext); }
%%
int yywrap()
{
return 1;
}
int main()
{
yyin = fopen("temp.txt", "r");
outputFile = fopen("output.txt", "w");
yylex();
fclose(yyin);
fclose(outputFile);
return 0;
}
