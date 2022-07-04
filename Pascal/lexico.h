#ifndef _LEXICO_H_
#define _LEXICO_H_

// Retorna o inteiro que pertence ao token lido
// Para cada proxima execucao, le o proximo token
int get_token();

// Pega a linha
int getLinha();

// Pega a coluna
int getColuna();

// Pega o ultimo token lido
char* get_ultimo_token_lido();

// Aumenta +1 o valor da linha
void linha_acrescentar();

// Aumenta +1 o valor da coluna
void coluna_acrescentar();

// Coluna recebe o valor Zero
void coluna_zerada();

#endif