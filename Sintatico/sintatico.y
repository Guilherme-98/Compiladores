%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char* yytext;
extern int yyleng;
extern int line;
extern int column;
extern int error_column;
extern int error_flag;
extern int flag_end_line;
extern void print_line_aux();

void yyerror(void* s);

void print_error_syntax() {
	error_flag = 0;
	int i;
	printf("error:syntax:%d:%d: %s", line, (column - yyleng), yytext);
	printf("\n");

	print_line_aux();

	while(!flag_end_line) {
		yylex();
		if(!flag_end_line) {
			printf("%s", yytext);
		}
	}

	printf("\n");
	for(i = 1; i < (error_column); i++) {
		printf(" ");
	}
	printf("^");
	exit(0);
}

%}

%token ADD_ASSIGN
%token ASSIGN
%token BITWISE_AND
%token BITWISE_NOT
%token BITWISE_OR
%token BITWISE_XOR
%token CHAR
%token CHARACTER
%token COLON
%token COMMA
%token DEC
%token DEFINE
%token DIV
%token DO
%token ELSE
%token ENDFILE
%token EQUAL
%token EXIT
%token FOR
%token GREATER_EQUAL
%token GREATER_THAN
%token IDENTIFIER
%token IF
%token INC
%token INT
%token LESS_EQUAL
%token LESS_THAN
%token LOGICAL_AND
%token LOGICAL_OR
%token L_CURLY_BRACKET
%token L_PAREN
%token L_SHIFT
%token L_SQUARE_BRACKET
%token MINUS
%token MINUS_ASSIGN
%token MULTIPLY
%token NOT
%token NOT_EQUAL
%token NUMBER_SIGN
%token NUM_HEXA
%token NUM_INTEGER
%token NUM_OCTAL
%token PLUS
%token PRINTF
%token REMAINDER
%token RETURN
%token R_CURLY_BRACKET
%token R_PAREN
%token R_SHIFT
%token R_SQUARE_BRACKET
%token SCANF
%token SEMICOLON
%token STRING
%token TERNARY_CONDITIONAL
%token VOID
%token WHILE

%start sintatico

%%

sintatico: programa ENDFILE { printf("SUCCESSFUL COMPILATION."); exit(0); };

//Programa
programa: declaracao programa_1 { }
	| funcao programa_1 { }
;

//declaracaoaracoes
programa_1: declaracao programa_1 { }
	| funcao programa_1 { }
	| %empty { }
;

//Funcao
funcao: tipo loop_multiplicativo IDENTIFIER parametro L_CURLY_BRACKET loop_declaracao_var comando R_CURLY_BRACKET { }
;

//declaracaoaracao de variavies 
declaracao: NUMBER_SIGN DEFINE IDENTIFIER expressao { }
	| declaracao_var { }
	| declaracao_prot { }
;

declaracao_var: tipo loop_multiplicativo IDENTIFIER loop_chaves_expressao declaracao_var_1 SEMICOLON { }
	| tipo loop_multiplicativo IDENTIFIER loop_chaves_expressao ASSIGN expressao_atr declaracao_var_1 SEMICOLON { }
;

declaracao_var_1: declaracao_var_1 COMMA loop_multiplicativo IDENTIFIER loop_chaves_expressao { }
	| declaracao_var_1 COMMA loop_multiplicativo IDENTIFIER loop_chaves_expressao ASSIGN expressao_atr { }
	| %empty { }
;

//declaracaoaracao de prototipo
declaracao_prot: tipo loop_multiplicativo IDENTIFIER parametro SEMICOLON { }
;

//parametro
parametro: L_PAREN parametro_1 R_PAREN { }
;

parametro_1: tipo loop_multiplicativo IDENTIFIER loop_chaves_expressao parametro_2 { }
	| %empty { }
;

parametro_2: parametro_2 COMMA tipo loop_multiplicativo IDENTIFIER loop_chaves_expressao { }
	| %empty { }
;

//Tipo
tipo: INT { }
	| CHAR { }
	| VOID { }
;

//Bloco
bloco: L_CURLY_BRACKET comando R_CURLY_BRACKET { }
;

//Comando
comando: lista_comando loop_lista_comando { }
;

//Lista de comando
lista_comando: DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON { }
	| IF L_PAREN expressao R_PAREN bloco { }
	| IF L_PAREN expressao R_PAREN bloco ELSE bloco { }
	| WHILE L_PAREN expressao R_PAREN bloco { }
	| FOR L_PAREN SEMICOLON SEMICOLON R_PAREN bloco { }
	| FOR L_PAREN expressao SEMICOLON expressao SEMICOLON expressao R_PAREN bloco { }
	| FOR L_PAREN expressao SEMICOLON SEMICOLON R_PAREN bloco { }
	| FOR L_PAREN SEMICOLON expressao SEMICOLON R_PAREN bloco { }
	| FOR L_PAREN SEMICOLON SEMICOLON expressao R_PAREN bloco { }
	| FOR L_PAREN expressao SEMICOLON expressao SEMICOLON R_PAREN bloco { }
	| FOR L_PAREN SEMICOLON expressao SEMICOLON expressao R_PAREN bloco { }
	| FOR L_PAREN expressao SEMICOLON SEMICOLON expressao R_PAREN bloco { }
	| PRINTF L_PAREN STRING R_PAREN SEMICOLON { }
	| PRINTF L_PAREN STRING COMMA expressao R_PAREN SEMICOLON { }
	| SCANF R_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON { }
	| EXIT L_PAREN expressao R_PAREN SEMICOLON { }
	| RETURN SEMICOLON { }
	| RETURN expressao SEMICOLON { } 
	| expressao SEMICOLON { }
	| SEMICOLON { }
	| bloco { }
;

//expressaoressao
expressao: expressao_atr loop_virgula_expressao_atr { }
;

//expressaoressao de atribuicao
expressao_atr: expressao_cond { }
	| expressao_unaria ASSIGN expressao_atr { }
	| expressao_unaria ADD_ASSIGN expressao_atr { }
	| expressao_unaria MINUS_ASSIGN expressao_atr { }
;

//expressaoressao condicional
expressao_cond: expressao_or_log { }
	| expressao_or_log TERNARY_CONDITIONAL expressao COLON expressao_cond { }
;

//expressaoressao OR logico
expressao_or_log: expressao_and_log loop_expressao_and_log { }
;

//expressaoressao AND logico
expressao_and_log: expressao_or loop_expressao_or { }
;

//expressaoressao OR
expressao_or: expressao_xor loop_expressao_xor { }
;

//Espressao XOR
expressao_xor: expressao_and loop_expressao_and { }
;

//expressaoressao AND
expressao_and: expressao_igualdade loop_expressao_igualdade { }
;

//expressaoressao de igualdade
expressao_igualdade: expressao_relacional loop_expressao_relacional { }
;

//expressaoressao relacional
expressao_relacional: expressao_shift loop_expressao_shift { }
;

//expressaoressao shift
expressao_shift: expressao_aditiva loop_expressao_aditiva { }
;

//expressaoressao aditiva
expressao_aditiva: expressao_multiplicativa loop_expressao_multiplicativa { }
;

//expressaoressao multiplicativa
expressao_multiplicativa: expressao_cast loop_expressao_cast { }
;

//expressaoressao cast
expressao_cast: expressao_unaria { }
	| L_PAREN tipo loop_multiplicativo R_PAREN expressao_cast { }
;

//expressaoressao unaria
expressao_unaria: expressao_posfix { }
	| INC expressao_unaria { }
	| DEC expressao_unaria { }
	| BITWISE_AND expressao_cast { }
	| MULTIPLY expressao_cast { }
	| PLUS expressao_cast { }
	| MINUS expressao_cast { }
	| BITWISE_NOT expressao_cast { }
	| NOT expressao_cast { }
;

//expressaoressao pos-fixa
expressao_posfix: expressao_primaria { }
	| expressao_posfix L_SQUARE_BRACKET expressao R_SQUARE_BRACKET { }
	| expressao_posfix INC { }
	| expressao_posfix DEC { }
	| expressao_posfix L_PAREN R_PAREN { }
	| expressao_posfix L_PAREN expressao_atr loop_virgula_expressao_atr R_PAREN { }
;

//expressaoressao primaria
expressao_primaria: IDENTIFIER { }
	| num { }
	| CHARACTER { }
	| STRING { }
	| L_PAREN expressao R_PAREN { }
;

//Numero
num: NUM_INTEGER { }
	| NUM_HEXA { }
	| NUM_OCTAL { }
;

//Loop multiplicativo 
loop_multiplicativo: loop_multiplicativo MULTIPLY{ }
	| %empty { }
;

//Loop declaracaoaracao de variaveis 
loop_declaracao_var: loop_declaracao_var declaracao_var { }
	| %empty { }
;

//Loop chaves
loop_chaves_expressao: loop_chaves_expressao L_SQUARE_BRACKET expressao R_SQUARE_BRACKET { }
	| %empty { }
;

//Lopp lista de comando
loop_lista_comando: loop_lista_comando lista_comando { }
	| %empty { }
;

//Loop virgula expressaoressao de atribuicao
loop_virgula_expressao_atr: loop_virgula_expressao_atr COMMA expressao_atr { }
	| %empty { }
;

//Loop empressao AND logico
loop_expressao_and_log: loop_expressao_and_log LOGICAL_OR expressao_and_log { }
	| %empty { }
;

//Loop expressaoressao OR
loop_expressao_or: loop_expressao_or LOGICAL_AND expressao_or { }
	| %empty { }
;

//Loop expressaoressao XOR
loop_expressao_xor: loop_expressao_xor BITWISE_OR expressao_xor { }
	| %empty { }
;

//Loop expressaoressao AND
loop_expressao_and: loop_expressao_and BITWISE_XOR expressao_and { }
	| %empty { }
;

//Loop expressaoressao de igualdade
loop_expressao_igualdade: loop_expressao_igualdade BITWISE_AND expressao_igualdade { }
	| %empty { }
;

//Loop expressaoressao relacional
loop_expressao_relacional: loop_expressao_relacional EQUAL expressao_relacional { }
	| loop_expressao_relacional NOT_EQUAL expressao_relacional { }
	| %empty { }
;

//Loop expressaoressao shift
loop_expressao_shift: loop_expressao_shift LESS_THAN expressao_shift { }
	| loop_expressao_shift LESS_EQUAL expressao_shift { }
	| loop_expressao_shift GREATER_THAN expressao_shift { }
	| loop_expressao_shift GREATER_EQUAL expressao_shift { }
	| %empty { }
;

//Loop expressaoressao aditiva
loop_expressao_aditiva: loop_expressao_aditiva L_SHIFT expressao_aditiva { }
	| loop_expressao_aditiva R_SHIFT expressao_aditiva { }
	| %empty { }
;

//Loop expressaoressao multiplicativa
loop_expressao_multiplicativa: loop_expressao_multiplicativa PLUS expressao_multiplicativa { }
	| loop_expressao_multiplicativa MINUS expressao_multiplicativa { }
	| %empty { }
;

//Loop expressaoressao cast
loop_expressao_cast: loop_expressao_cast MULTIPLY expressao_cast { }
	| loop_expressao_cast DIV expressao_cast { }
	| loop_expressao_cast REMAINDER expressao_cast { }
	| %empty { }
;

%%

void yyerror (void* s) {
	error_column = column - yyleng;
	print_error_syntax();
}

int main(int argc, char** argv) {
	yyparse();
	return 0;
}