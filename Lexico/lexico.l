/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
	#include<stdbool.h>

	int line = 1;
	int column = 1;

	int comment_line = 0;
	int comment_column = 0;

	bool first = true;

	void printfVerification(){
		if(first){
            first = false;
        }
        else{
            printf("\n");
        }
	}

	void printString_Caracter(char str[]){
        char *aux = str;
        aux++;

        aux[strlen(aux)-1] = 0;
        printf("(%s)", aux);
    }
%}

%x comment
%x comment_slashes

%%

\n			                 {line++; column = 1;}
[\f\t\r ]*	                 {column += yyleng;}

"/*"				         {BEGIN(comment); comment_line = line; comment_column = column; column += yyleng;}
<comment><<EOF>>	         {BEGIN(INITIAL); printfVerification(); printf("error:lexical:%d:%d: unterminated comment", comment_line, comment_column);}
<comment>"*/"		         {column += yyleng; BEGIN(INITIAL);}
<comment>\n			         {line++; column = 1;}			
<comment>.			         {column += yyleng;}

"//"						 {BEGIN(comment_slashes);}
<comment_slashes><<EOF>>	 {BEGIN(INITIAL);}
<comment_slashes>\n			 {BEGIN(INITIAL); line++; column = 1;}			
<comment_slashes>.			 {column += yyleng;}

"void"                  {printfVerification(); printf("VOID"); column += strlen(yytext);}
"int"                   {printfVerification(); printf("INT"); column += strlen(yytext);}
"char"                  {printfVerification(); printf("CHAR"); column += strlen(yytext);}
"return"                {printfVerification(); printf("RETURN"); column += strlen(yytext);}
"break"                 {printfVerification(); printf("BREAK"); column += strlen(yytext);}
"switch"                {printfVerification(); printf("SWITCH"); column += strlen(yytext);}
"case"                  {printfVerification(); printf("CASE"); column += strlen(yytext);}
"default"               {printfVerification(); printf("DEFAULT"); column += strlen(yytext);}
"do"                    {printfVerification(); printf("DO"); column += strlen(yytext);}
"while"                 {printfVerification(); printf("WHILE"); column += strlen(yytext);}
"for"                   {printfVerification(); printf("FOR"); column += strlen(yytext);}
"if"                    {printfVerification(); printf("IF"); column += strlen(yytext);}
"else"                  {printfVerification(); printf("ELSE"); column += strlen(yytext);}
"typedef"               {printfVerification(); printf("TYPEDEF"); column += strlen(yytext);} 
"struct"                {printfVerification(); printf("STRUCT"); column += strlen(yytext);}
"+"                     {printfVerification(); printf("PLUS"); column += strlen(yytext);}
"-"                     {printfVerification(); printf("MINUS"); column += strlen(yytext);}
"*"                     {printfVerification(); printf("MULTIPLY"); column += strlen(yytext);}
"/"                     {printfVerification(); printf("DIV"); column += strlen(yytext);}
"%"                     {printfVerification(); printf("REMAINDER"); column += strlen(yytext);}
"++"                    {printfVerification(); printf("INC"); column += strlen(yytext);}
"--"                    {printfVerification(); printf("DEC"); column += strlen(yytext);}
"&"                     {printfVerification(); printf("BITWISE_AND"); column += strlen(yytext);}
"|"                     {printfVerification(); printf("BITWISE_OR"); column += strlen(yytext);}
"~"                     {printfVerification(); printf("BITWISE_NOT"); column += strlen(yytext);}
"^"                     {printfVerification(); printf("BITWISE_XOR"); column += strlen(yytext);}
"!"                     {printfVerification(); printf("NOT"); column += strlen(yytext);}
"&&"                    {printfVerification(); printf("LOGICAL_AND"); column += strlen(yytext);}
"||"                    {printfVerification(); printf("LOGICAL_OR"); column += strlen(yytext);}
"=="                    {printfVerification(); printf("EQUAL"); column += strlen(yytext);}
"!="                    {printfVerification(); printf("NOT_EQUAL"); column += strlen(yytext);}
"<"                     {printfVerification(); printf("LESS_THAN"); column += strlen(yytext);}
">"                     {printfVerification(); printf("GREATER_THAN"); column += strlen(yytext);}
"<="                    {printfVerification(); printf("LESS_EQUAL"); column += strlen(yytext);}
">="                    {printfVerification(); printf("GREATER_EQUAL"); column += strlen(yytext);}
">>"                    {printfVerification(); printf("R_SHIFT"); column += strlen(yytext);}
"<<"                    {printfVerification(); printf("L_SHIFT"); column += strlen(yytext);}
"="                     {printfVerification(); printf("ASSIGN"); column += strlen(yytext);}
"+="                    {printfVerification(); printf("ADD_ASSIGN"); column += strlen(yytext);}
"-="                    {printfVerification(); printf("MINUS_ASSIGN"); column += strlen(yytext);}
";"                     {printfVerification(); printf("SEMICOLON"); column += strlen(yytext);}
","                     {printfVerification(); printf("COMMA"); column += strlen(yytext);}
":"                     {printfVerification(); printf("COLON"); column += strlen(yytext);}
"("                     {printfVerification(); printf("L_PAREN"); column += strlen(yytext);}
")"                     {printfVerification(); printf("R_PAREN"); column += strlen(yytext);}
"{"                     {printfVerification(); printf("L_CURLY_BRACKET"); column += strlen(yytext);}
"}"                     {printfVerification(); printf("R_CURLY_BRACKET"); column += strlen(yytext);}
"["                     {printfVerification(); printf("L_SQUARE_BRACKET"); column += strlen(yytext);}
"]"                     {printfVerification(); printf("R_SQUARE_BRACKET"); column += strlen(yytext);}
"?"                     {printfVerification(); printf("TERNARY_CONDITIONAL"); column += strlen(yytext);}
"#"                     {printfVerification(); printf("NUMBER_SIGN"); column += strlen(yytext);}
"->"                    {printfVerification(); printf("POINTER"); column += strlen(yytext);}
"printf"                {printfVerification(); printf("PRINTF"); column += strlen(yytext);}
"scanf"                 {printfVerification(); printf("SCANF"); column += strlen(yytext);}
"define"                {printfVerification(); printf("DEFINE"); column += strlen(yytext);}
"exit"                  {printfVerification(); printf("EXIT"); column += strlen(yytext);}

[\\][a|b|f|n|r|t|v|"\\"|'|"|?|0]                     {printfVerification(); printf("CHARACTER(%s)", yytext);column += strlen(yytext);}
([a-z]|"_"|[A-Z])([a-z]|"_"|[A-Z]|[0-9])*	         {printfVerification(); printf("IDENTIFIER(%s)", yytext); column += yyleng;(yytext);}
\"(\\.|[^"\\])*\"                                    {printfVerification(); printf("STRING"); printString_Caracter(yytext); column += yyleng;(yytext);}
"\'"(.|"\\".)"\'"  			                         {printfVerification(); printf("CHARACTER"); printString_Caracter(yytext); column += yyleng;(yytext);}

[0][x|X][0-9A-Fa-f]+ 		                         {printfVerification(); printf("NUM_HEXA(%s)", yytext); column += yyleng;(yytext);}
[0][1-7][0-7]*				                         {printfVerification(); printf("NUM_OCTAL(%s)", yytext); column += yyleng;(yytext);}
[0-9]+					                             {printfVerification(); printf("NUM_INTEGER(%s)", yytext); column += yyleng;(yytext);}

.	{printfVerification(); printf("error:lexical:%d:%d: %s", line, column, yytext); column += yyleng;}

%%

int main(int argc, char **argv){
	
	yylex();
	return 0;
}