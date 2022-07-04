#ifndef T3_ESTRUTURAS_H
#define T3_ESTRUTURAS_H

typedef void* Grafo;
typedef void* Vertice;
typedef void* Pilha;

Grafo estruturas_criarGrafo();

void estruturas_setIdGrafo(Grafo grafo, int id) ;

void estruturas_setRegistradoresFisicos(Grafo grafoParametro, int registradoresFisicos);

void estruturas_setPrimeiroRegistradorLogico(Grafo grafoParametro, int primeiroRegistradorLogico);

int estruturas_getPrimeiroRegistradorLogico(Grafo grafoParametro);

void estruturas_alterarMatrizAdjacencia(Grafo grafoParametro, int i, int j, int valor);

int** estruturas_getMatrizAdjacencia(Grafo grafoParametro);

void estruturas_setMatrizAdjacenciaOriginal(Grafo grafoParametro);

void estruturas_resetMatrizAdjacencia(Grafo grafoParametro);

int** estruturas_getMatrizAdjacenciaOriginal(Grafo grafoParametro);

int estruturas_getTamanhoGrafo(Grafo grafoParametro);

int estruturas_getRegistradoresFisicos(Grafo grafoParametro);

Vertice estruturas_getVertice(Grafo grafoParametro, int indice);

void estruturas_removerVerticeMatrizAdjacencia(Grafo grafoParametro, int indice);

void estruturas_removerVerticeMaiorGrau(Grafo grafoParametro, Pilha pilha, int inicio, int tamanho);

void estruturas_restaurarVerticeMatrizAdjacencia(Grafo grafoParametro, int indice);

void estruturas_criarInserirVertice(Grafo grafoParametro, int indice, int tamanhoRegistradoresFisicos);

int estruturas_registradorLogicoAlocado(Grafo grafoParametro, int indice);

Pilha estruturas_criarPilha(int tamanhoMaximo);

void estruturas_limparPilha(Pilha pilhaParametro);

void estruturas_pushPilha(Pilha pilhaParametro, Vertice verticeParametro);

int estruturas_isIndiceNaPilha(Pilha pilhaParametro, int indice);

void estruturas_popPilha(Pilha pilhaParametro);

void estruturas_desempilhar(Pilha pilhaParametro, Grafo grafoParametro, int cores);

void estruturas_exibirRelatorio(Grafo grafoParametro);

void estruturas_freeEstruturas(Grafo grafoParametro, Pilha pilhaParametro);

#endif //T3_ESTRUTURAS_H