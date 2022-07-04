#include "lexico.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

static int coluna = 0;
static int linha = 1;
static char ultimo_token_lido[64];

int getLinha() {
	return linha;
}

int getColuna() {
	return coluna;
}

void linha_acrescentar() {
	linha++;
}

void coluna_acrescentar() {
	coluna++;
}

void coluna_zerada() {
	coluna = 0;
}

char* get_ultimo_token_lido() {
	return ultimo_token_lido;
}

int get_token() {
	char caract_lido;
	int ultimo_final_cursor = 0;
	int ultimo_estado_final = 0;
	int atual_estado = 1;
	int atual_cursor = -1;

	memset(ultimo_token_lido, 0, 64);

	inicio();

	while(1) {
		caract_lido = fgetc(stdin);
		atual_cursor++;
		coluna++;

		ultimo_token_lido[atual_cursor] = caract_lido;
		
		atual_estado = get_estado_prox(atual_estado, caract_lido);

		if(atual_estado == 0) {
			if(ultimo_estado_final == 0) {
				printf("ERRO LEXICO. Linha: %d Coluna: %d -> %c", linha, coluna, caract_lido);
				exit(0);
			}

			else {
				fseek(stdin, (ultimo_final_cursor - atual_cursor),SEEK_CUR);
				coluna = coluna - (atual_cursor - ultimo_final_cursor);
				
				ultimo_token_lido[atual_cursor] = '\0';

				return retornar_token(ultimo_estado_final);
			}
		}

		if(final_estado(atual_estado)) {
			ultimo_estado_final = atual_estado;
			ultimo_final_cursor = atual_cursor;
		}
	}
}