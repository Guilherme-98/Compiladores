%option noyywrap

%{
#include "sintatico.tab.h"

int line = 1;
int column = 1;
int comment_start_line = 0;
int comment_start_column = 0;
int flag_end_line = 0;
int error_column = 0;
int error_flag = 1;

char line_aux[2048];

extern void print_error_syntax();

void print_line_aux() {
    printf("%s", line_aux);
}

%}

%x comment
%x comment_slashes

%%

\n			                {line++; column = 1; memset(line_aux, 0, 2048); if(!error_flag){flag_end_line = 1;}}
[\f\t\r ]*	                {column += yyleng; strcat(line_aux, yytext); if(!error_flag && !flag_end_line){printf("%s", yytext);}}

"/*"				        {BEGIN(comment); comment_start_line = line; comment_start_column = column; column += yyleng;}
<comment><<EOF>>	        {BEGIN(INITIAL); printf("error:lexical:%d:%d: unterminated comment", comment_start_line, comment_start_column); return 0;}
<comment>"*/"		        {column += yyleng; BEGIN(INITIAL);}
<comment>\n			        {line++; column = 1;}			
<comment>.			        {column += yyleng;}

"//"						{BEGIN(comment_slashes);}
<comment_slashes><<EOF>>	{BEGIN(INITIAL); return 0;}
<comment_slashes>\n			{BEGIN(INITIAL); line++; column = 1;}			
<comment_slashes>.			{column += yyleng;}

"void"		{column += yyleng; strcat(line_aux, yytext); return VOID;}
"int"		{column += yyleng; strcat(line_aux, yytext); return INT;}
"char"		{column += yyleng; strcat(line_aux, yytext); return CHAR;}
"return"	{column += yyleng; strcat(line_aux, yytext); return RETURN;}
"break"		{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"switch"	{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"case"		{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"default"	{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"do"		{column += yyleng; strcat(line_aux, yytext); return DO;}
"while"		{column += yyleng; strcat(line_aux, yytext); return WHILE;}
"for"		{column += yyleng; strcat(line_aux, yytext); return FOR;}
"if"		{column += yyleng; strcat(line_aux, yytext); return IF;}
"else"		{column += yyleng; strcat(line_aux, yytext); return ELSE;}
"typedef"	{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"struct"	{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"printf"	{column += yyleng; strcat(line_aux, yytext); return PRINTF;}
"scanf"		{column += yyleng; strcat(line_aux, yytext); return SCANF;}
"define"	{column += yyleng; strcat(line_aux, yytext); return DEFINE;}
"exit"		{column += yyleng; strcat(line_aux, yytext); return EXIT;}
"++"		{column += yyleng; strcat(line_aux, yytext); return INC;}
"--"		{column += yyleng; strcat(line_aux, yytext); return DEC;}
"&&"		{column += yyleng; strcat(line_aux, yytext); return LOGICAL_AND;}
"||"		{column += yyleng; strcat(line_aux, yytext); return LOGICAL_OR;}
"=="		{column += yyleng; strcat(line_aux, yytext); return EQUAL;}
"!="		{column += yyleng; strcat(line_aux, yytext); return NOT_EQUAL;}
"<="		{column += yyleng; strcat(line_aux, yytext); return LESS_EQUAL;}
">="		{column += yyleng; strcat(line_aux, yytext); return GREATER_EQUAL;}
">>"		{column += yyleng; strcat(line_aux, yytext); return R_SHIFT;}
"<<"		{column += yyleng; strcat(line_aux, yytext); return L_SHIFT;}
"+="		{column += yyleng; strcat(line_aux, yytext); return ADD_ASSIGN;}
"-="		{column += yyleng; strcat(line_aux, yytext); return MINUS_ASSIGN;}
"->"		{column += yyleng; strcat(line_aux, yytext); if(error_flag){error_column=column-yyleng; print_error_syntax();}}
"+"			{column += yyleng; strcat(line_aux, yytext); return PLUS;}
"-"			{column += yyleng; strcat(line_aux, yytext); return MINUS;}
"*"			{column += yyleng; strcat(line_aux, yytext); return MULTIPLY;}
"/"			{column += yyleng; strcat(line_aux, yytext); return DIV;}
"%"			{column += yyleng; strcat(line_aux, yytext); return REMAINDER;}
"&"			{column += yyleng; strcat(line_aux, yytext); return BITWISE_AND;}
"|"			{column += yyleng; strcat(line_aux, yytext); return BITWISE_OR;}
"~"			{column += yyleng; strcat(line_aux, yytext); return BITWISE_NOT;}
"^"			{column += yyleng; strcat(line_aux, yytext); return BITWISE_XOR;}
"!"			{column += yyleng; strcat(line_aux, yytext); return NOT;}
"<"			{column += yyleng; strcat(line_aux, yytext); return LESS_THAN;}
">"			{column += yyleng; strcat(line_aux, yytext); return GREATER_THAN;}
"="			{column += yyleng; strcat(line_aux, yytext); return ASSIGN;}
";"			{column += yyleng; strcat(line_aux, yytext); return SEMICOLON;}
","			{column += yyleng; strcat(line_aux, yytext); return COMMA;}
":"			{column += yyleng; strcat(line_aux, yytext); return COLON;}
"("			{column += yyleng; strcat(line_aux, yytext); return L_PAREN;}
")"			{column += yyleng; strcat(line_aux, yytext); return R_PAREN;}
"{"			{column += yyleng; strcat(line_aux, yytext); return L_CURLY_BRACKET;}
"}"			{column += yyleng; strcat(line_aux, yytext); return R_CURLY_BRACKET;}
"["			{column += yyleng; strcat(line_aux, yytext); return L_SQUARE_BRACKET;}
"]"			{column += yyleng; strcat(line_aux, yytext); return R_SQUARE_BRACKET;}
"?"			{column += yyleng; strcat(line_aux, yytext); return TERNARY_CONDITIONAL;}
"#"			{column += yyleng; strcat(line_aux, yytext); return NUMBER_SIGN;}

\"(\\.|[^"\\])*\"	                            {column += yyleng; strcat(line_aux, yytext); return STRING;}
([a-z]|"_"|[A-Z])([a-z]|"_"|[A-Z]|[0-9])*	    {column += yyleng; strcat(line_aux, yytext); return IDENTIFIER;}
[\\][a|b|f|n|r|t|v|"\\"|'|"|?|0]                {column += yyleng; strcat(line_aux, yytext); return CHARACTER;}
"\'"(.|"\\".)"\'"			                    {column += yyleng; strcat(line_aux, yytext); return CHARACTER;}

[0][x|X][0-9A-Fa-f]+ 	                        {column += yyleng; strcat(line_aux, yytext); return NUM_HEXA;}
[0][1-7][0-7]*					                {column += yyleng; strcat(line_aux, yytext); return NUM_OCTAL;}
[0-9]+					                        {column += yyleng; strcat(line_aux, yytext); return NUM_INTEGER;}

<<EOF>>					                        {if(!error_flag){flag_end_line = 1;} return ENDFILE;}

.						                        {printf("error:lexical:%d:%d: %s", line, column, yytext); column += yyleng; exit(0);}

%%