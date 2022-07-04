#ifndef _AUTOMATO_H_
#define _AUTOMATO_H_

// Retorna o proximo estado com a leitura de um caractere
int get_estado_prox(int estado, char caract_lido);

// Ignora espacos, tabs e quebras de linha no inicio da cadeia
void inicio();

// Retorna 1 caso o estado seja final - Caso contrario retorna 0
int final_estado(int estado);

// Retorna o token relacionado ao final do estado
int retornar_token(int final_estado);

#endif