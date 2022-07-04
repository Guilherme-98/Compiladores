#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "sintatico.h"

int token;

void print_erro();

void erro() {
	printf("ERRO DE SINTAXE. Linha: %d -> \"%s\"", getLinha(), get_ultimo_token_lido());
	exit(0);
}

void avancar() {
	token = get_token();
	while(token == COMMENT) {
		token = get_token();
	}
}

void comer(int t) {
	if(token == t) {
		avancar();
	}
	else {
		erro();
	}
}

void comer_ultimo(int t) {
	if(token != t) {
		erro();
	}
}

void programa();
void bloco();
void bloco_1();
void bloco_2();
void bloco_auxiliar_1();
void tipo();
void tipo_auxiliar_1();
void parametros_formais();
void parametros_formais_auxiliar_1();
void parametros_formais_auxiliar_2();
void comando();
void comando_auxiliar_1();
void comando_auxiliar_2();
void loop_comando();
void expressao();
void expressao_auxiliar_1();
void expressao_simples();
void expressao_simples_auxiliar_1();
void loop_expressao();
void termo();
void termo_auxiliar_1();
void fator();
void fator_auxiliar_1();
void fator_auxiliar_2();
void variavel_auxiliar_1();
void constante();
void loop_constante();
void loop_id();
void loop_var();
void sinal();

int main() {
	avancar();
	programa();
	printf("PROGRAMA CORRETO.");
	return 0;
}

void programa() {
	switch(token) {
		case PROGRAM: comer(PROGRAM); comer(ID); comer(SEMICOLON); bloco(); comer_ultimo(DOT); break;
		default: erro();
	}
}

void loop_comando() {
	switch(token) {
		case END: break;
		case SEMICOLON: comer(SEMICOLON); comando(); loop_comando(); break;
		default: erro();
	}
}

void loop_id() {
	switch(token) {
		case COLON: break;
		case COMMA: comer(COMMA); comer(ID); loop_id(); break;
		default: printf("gothere token:%d\n", token); erro();
	}
}

void loop_constante() {
	switch(token) {
		case R_SQUARE_BRACKET: break;
		case COMMA: comer(COMMA); constante(); loop_constante(); break;
		default: erro();
	}
}

void loop_var() {
	switch(token) {
		case ID: break;
		case VAR: comer(VAR); loop_var(); break;
		default: erro();
	}
}

void loop_expressao() {
	switch(token) {
		case R_BRACKET: break;
		case R_SQUARE_BRACKET: break;
		case COMMA: comer(COMMA); expressao(); loop_expressao(); break;
		default: erro();
	}
}

void sinal() {
	switch(token) {
		case NOT: break;
		case ID: break;
		case NUM: break;
		case L_BRACKET: break;
		case PLUS: comer(PLUS); break;
		case MINUS: comer(MINUS); break;
		default: erro();
	}
}

void bloco() {
	switch(token) {
		case BEGIN: bloco_1(); bloco_2(); comer(BEGIN); comando(); loop_comando(); comer(END); break;
		case FUNCTION: bloco_1(); bloco_2(); comer(BEGIN); comando(); loop_comando(); comer(END); break;
		case PROCEDURE: bloco_1(); bloco_2(); comer(BEGIN); comando(); loop_comando(); comer(END); break;
		case VAR: bloco_1(); bloco_2(); comer(BEGIN); comando(); loop_comando(); comer(END); break;
		default: erro();
	}
}

void bloco_1() {
	switch(token) {
		case BEGIN: break;
		case FUNCTION: break;
		case PROCEDURE: break;
		case VAR: comer(VAR); comer(ID); loop_id(); comer(COLON); tipo(); comer(SEMICOLON); bloco_auxiliar_1(); break;
		default: erro();
	}
}

void bloco_2() {
	switch(token) {
		case BEGIN: break;
		case FUNCTION: comer(FUNCTION); comer(ID); parametros_formais(); comer(COLON); comer(ID); comer(SEMICOLON); bloco(); comer(SEMICOLON); bloco_2(); break;
		case PROCEDURE: comer(PROCEDURE); comer(ID); parametros_formais(); comer(SEMICOLON); bloco(); comer(SEMICOLON); bloco_2(); break;
		default: erro();
	}
}

void bloco_auxiliar_1() {
	switch(token) {
		case BEGIN: break;
		case FUNCTION: break;
		case PROCEDURE: break;
		case ID: comer(ID); loop_id(); comer(COLON); tipo(); comer(SEMICOLON); bloco_auxiliar_1(); break;
		default: erro();
	}
}

void tipo() {
	switch(token) {
		case ARRAY: comer(ARRAY); comer(L_SQUARE_BRACKET); constante(); loop_constante(); comer(R_SQUARE_BRACKET); comer(OF); tipo(); break;
		case ID: comer(ID); tipo_auxiliar_1(); break; 
		case NUM: sinal(); comer(NUM); comer(DOUBLEDOT); constante(); break;
		case PLUS: sinal(); comer(NUM); comer(DOUBLEDOT); constante(); break;
		case MINUS: sinal(); comer(NUM); comer(DOUBLEDOT); constante(); break;
		default: erro();
	}
}

void tipo_auxiliar_1() {
	switch(token) {
		case R_SQUARE_BRACKET: break;
		case SEMICOLON: break;
		case DOUBLEDOT: comer(DOUBLEDOT); constante(); break;
		case COMMA: break; 
		default: erro();
	}
}

void parametros_formais() {
	switch(token) {
		case L_BRACKET: comer(L_BRACKET); parametros_formais_auxiliar_1(); parametros_formais_auxiliar_2(); comer(R_BRACKET); break;
		case COLON: break;
		case SEMICOLON: break;
		default: erro();
	}
}

void parametros_formais_auxiliar_1() {
	switch(token) {
		case VAR: loop_var(); comer(ID); loop_id(); comer(COLON); comer(ID); break;
		case ID: loop_var(); comer(ID); loop_id(); comer(COLON); comer(ID); break;
		default: erro();
	}	
}

void parametros_formais_auxiliar_2() {
	switch(token) {
		case R_BRACKET: break;
		case SEMICOLON: comer(SEMICOLON); parametros_formais_auxiliar_1(); parametros_formais_auxiliar_2(); break;
		default: erro();
	}	
}

void variavel_auxiliar_1() {
	switch(token) {
		case AND: break;
		case DIV: break;
		case DO: break;
		case END: break;
		case THEN: break;
		case PLUS: break;
		case MINUS: break;
		case TIMES: break;
		case EQUALS: break;
		case DIFFERENT: break;
		case LESS: break;
		case LESS_EQUAL: break;
		case GREATER: break;
		case GREATER_EQUAL: break;
		case R_BRACKET: break;
		case L_SQUARE_BRACKET: comer(L_SQUARE_BRACKET); expressao(); loop_expressao(); comer(R_SQUARE_BRACKET); variavel_auxiliar_1(); break;
		case R_SQUARE_BRACKET: break;
		case ASSIGNMENT: break;
		case SEMICOLON: break;
		case COMMA: break;
		default: erro();
	}
}

void comando() {
	switch(token) {
		case BEGIN: comer(BEGIN); comando(); loop_comando(); comer(END); break;
		case END: break;
		case IF: comer(IF); expressao(); comer(THEN); comer(BEGIN); comando(); loop_comando(); comer(END); comando_auxiliar_1(); break;
		case WHILE: comer(WHILE); expressao(); comer(DO); comando(); break;
		case ID: comer(ID); comando_auxiliar_2(); break;
		case SEMICOLON: break;
		default: erro();
	}
}

void comando_auxiliar_1() {
	switch(token) {
		case ELSE: comer(ELSE); comer(BEGIN); comando(); loop_comando(); comer(END); break;;
		case END: break;
		case SEMICOLON: break;
		default: erro();
	}
}

void comando_auxiliar_2() {
	switch(token) {
		case END: break;
		case L_BRACKET: comer(L_BRACKET); expressao(); loop_expressao(); comer(R_BRACKET); break;
		case L_SQUARE_BRACKET: variavel_auxiliar_1(); comer(ASSIGNMENT); expressao(); break;
		case ASSIGNMENT: variavel_auxiliar_1(); comer(ASSIGNMENT); expressao(); break;
		case SEMICOLON: break;
		default: erro();
	}
}

void expressao() {
	switch(token) {
		case NOT: expressao_simples(); expressao_auxiliar_1(); break;
		case ID: expressao_simples(); expressao_auxiliar_1(); break;
		case NUM: expressao_simples(); expressao_auxiliar_1(); break;
		case PLUS: expressao_simples(); expressao_auxiliar_1(); break;
		case MINUS: expressao_simples(); expressao_auxiliar_1(); break;
		case L_BRACKET: expressao_simples(); expressao_auxiliar_1(); break;
		default: erro();
	}
}

void expressao_auxiliar_1() {
	switch(token) {
		case DO: break;
		case END: break;
		case THEN: break;
		case EQUALS: comer(EQUALS); expressao_simples(); break;
		case DIFFERENT: comer(DIFFERENT); expressao_simples(); break;
		case LESS: comer(LESS); expressao_simples(); break;
		case LESS_EQUAL: comer(LESS_EQUAL); expressao_simples(); break;
		case GREATER: comer(GREATER); expressao_simples(); break;
		case GREATER_EQUAL: comer(GREATER_EQUAL); expressao_simples(); break;
		case R_BRACKET: break;
		case R_SQUARE_BRACKET: break;
		case SEMICOLON: break;
		case COMMA: break;
		default: erro();
	}
}

void expressao_simples() {
	switch(token) {
		case NOT: sinal(); termo(); expressao_simples_auxiliar_1(); break;
		case ID: sinal(); termo(); expressao_simples_auxiliar_1(); break;
		case NUM: sinal(); termo(); expressao_simples_auxiliar_1(); break;
		case PLUS: sinal(); termo(); expressao_simples_auxiliar_1(); break;
		case MINUS: sinal(); termo(); expressao_simples_auxiliar_1(); break;
		case L_BRACKET: sinal(); termo(); expressao_simples_auxiliar_1(); break;
		default: erro();
	}
}

void expressao_simples_auxiliar_1() {
	switch(token) {
		case DO: break;
		case END: break;
		case OR: comer(OR); termo(); expressao_simples_auxiliar_1(); break;
		case THEN: break;
		case PLUS: comer(PLUS); termo(); expressao_simples_auxiliar_1(); break;
		case MINUS: comer(MINUS); termo(); expressao_simples_auxiliar_1(); break;
		case EQUALS: break;
		case DIFFERENT: break;
		case LESS: break;
		case LESS_EQUAL: break;
		case GREATER: break;
		case GREATER_EQUAL: break;
		case R_BRACKET: break;
		case R_SQUARE_BRACKET: break;
		case SEMICOLON: break;
		case COMMA: break;
		default: erro();
	}
}

void termo() {
	switch(token) {
		case NOT: fator(); termo_auxiliar_1(); break;
		case ID: fator(); termo_auxiliar_1(); break;
		case NUM: fator(); termo_auxiliar_1(); break;
		case L_BRACKET: fator(); termo_auxiliar_1(); break;
		default: erro();
	}
}

void termo_auxiliar_1() {
	switch(token) {
		case AND: comer(AND); fator(); termo_auxiliar_1(); break;
		case DIV: comer(DIV); fator(); termo_auxiliar_1(); break;
		case DO: break;
		case END: break;
		case OR: break;
		case THEN: break;
		case PLUS: break;
		case MINUS: break;
		case TIMES: comer(TIMES); fator(); termo_auxiliar_1(); break;
		case EQUALS: break;
		case DIFFERENT: break;
		case LESS: break;
		case LESS_EQUAL: break;
		case GREATER: break;
		case GREATER_EQUAL: break;
		case R_BRACKET: break;
		case R_SQUARE_BRACKET: break;
		case SEMICOLON: break;
		case COLON: break;
		default: erro();
	}
}

void fator() {
	switch(token) {
		case NOT: comer(NOT); fator(); break;
		case ID: comer(ID); fator_auxiliar_1(); break;
		case NUM: comer(NUM); break;
		case L_BRACKET: comer(L_BRACKET); expressao(); comer(R_BRACKET); break;
		default: erro();
	}
}

void fator_auxiliar_1() {
	switch(token) {
		case AND: break;
		case DIV: break;
		case DO: break;
		case END: break;
		case OR: break;
		case THEN: break;
		case PLUS: break;
		case MINUS: break;
		case TIMES: break;
		case EQUALS: break;
		case DIFFERENT: break;
		case LESS: break;
		case LESS_EQUAL: break;
		case GREATER: break;
		case GREATER_EQUAL: break;
		case L_BRACKET: comer(L_BRACKET); fator_auxiliar_2(); comer(R_BRACKET); break;
		case R_BRACKET: break;
		case L_SQUARE_BRACKET: variavel_auxiliar_1(); break;
		case R_SQUARE_BRACKET: break;
		case SEMICOLON: break;
		case COMMA: break;
		default: erro();
	}
}

void fator_auxiliar_2() {
	switch(token) {
		case NOT: expressao(); loop_expressao(); break;
		case ID: expressao(); loop_expressao(); break;
		case NUM: expressao(); loop_expressao(); break;
		case PLUS: expressao(); loop_expressao(); break;
		case LESS: expressao(); loop_expressao(); break;
		case L_BRACKET: expressao(); loop_expressao(); break;
		case R_BRACKET: break;
		default: erro();
	}
}

void constante() {
	switch(token) {
		case NUM: sinal(); comer(NUM); break;
		case PLUS: sinal(); comer(NUM); break;
		case MINUS: sinal(); comer(NUM); break;
		default: erro();
	}
}