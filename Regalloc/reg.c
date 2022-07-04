#include "reg.h"
#include "estruturas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Grafo grafo;
static Pilha pilha;

void criarGrafo() {
    int maiorRegistrador;
    int buffer;
    fscanf(stdin, "Grafo %d:\n", &buffer);
    fscanf(stdin, "K=%d\n", &buffer);
    while (1) {
        fscanf(stdin, "%d --> ", &maiorRegistrador);
        while (fgetc(stdin) != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            fscanf(stdin, "%d", &buffer);
            if (feof(stdin)) {
                break;
            }
        }
        if (feof(stdin)) {
            break;
        }
    }
    grafo = estruturas_criarGrafo(maiorRegistrador + 1);
    fseek(stdin, 0, SEEK_SET);
}

void reg_build() {
    int idGrafo;
    int qtdRegistradores;
    int registradorAtual;
    int registradorInterferencia;
    int primeiraIteracao = 1;

    criarGrafo();

    fscanf(stdin, "Grafo %d:\n", &idGrafo);
    fscanf(stdin, "K=%d\n", &qtdRegistradores);

    estruturas_setIdGrafo(grafo, idGrafo);
    estruturas_setRegistradoresFisicos(grafo, qtdRegistradores);
    
    printf("Graph %d -> Physical Registers: %d\n", idGrafo, qtdRegistradores);
    printf("----------------------------------------\n");

    while (1) {
        fscanf(stdin, "%d --> ", &registradorAtual);

        if (primeiraIteracao) {
            estruturas_setPrimeiroRegistradorLogico(grafo, registradorAtual);
            primeiraIteracao = 0;
        }

        estruturas_criarInserirVertice(grafo, registradorAtual, qtdRegistradores);
        while (fgetc(stdin) != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            fscanf(stdin, "%d", &registradorInterferencia);

            estruturas_alterarMatrizAdjacencia(grafo, registradorAtual, registradorInterferencia, 1);

            if (feof(stdin)) {
                break;
            }
        }
        if (feof(stdin)) {
            break;
        }
    }
}

void reg_simplify() {
    int i;
    int j;
    int k;
    int inicio;
    int tamanho;
    int grau;
    int **matrizAdjacencia;
    int modificaoPilha;
    int menorGrau;
    int indicePush;
    int spill;

    k = estruturas_getRegistradoresFisicos(grafo);
    inicio = estruturas_getPrimeiroRegistradorLogico(grafo);
    tamanho = estruturas_getTamanhoGrafo(grafo);
    matrizAdjacencia = estruturas_getMatrizAdjacencia(grafo);
    estruturas_setMatrizAdjacenciaOriginal(grafo);
    pilha = estruturas_criarPilha(tamanho);

    while (k > 1) {

        printf("----------------------------------------\n");
        printf("K = %d\n\n", k);

        estruturas_limparPilha(pilha);
        modificaoPilha = 1;

        estruturas_resetMatrizAdjacencia(grafo);

        while (modificaoPilha) {
            modificaoPilha = 0;
            menorGrau = tamanho;
            for (i = inicio; i < tamanho; i++) {
                grau = 0;
                if(estruturas_registradorLogicoAlocado(grafo, i)) {
                    for (j = 0; j < tamanho; j++) {
                        if (matrizAdjacencia[i][j] == 1) {
                            grau++;
                        }
                    }
                    if (grau < menorGrau) {
                        if (estruturas_isIndiceNaPilha(pilha, i) == 0) {
                            modificaoPilha = 1;
                            menorGrau = grau;
                            indicePush = i;
                        }
                    }
                }
            }
            if (modificaoPilha == 1) {
                if (menorGrau < k) {
                    estruturas_pushPilha(pilha, estruturas_getVertice(grafo, indicePush));
                    estruturas_removerVerticeMatrizAdjacencia(grafo, indicePush);
                    printf("Push: %d\n", indicePush);
                } else {
                    estruturas_removerVerticeMaiorGrau(grafo, pilha, inicio, tamanho);
                }
            }
        }
        estruturas_resetMatrizAdjacencia(grafo);
        estruturas_desempilhar(pilha, grafo, k);
        k--;
    }
    estruturas_exibirRelatorio(grafo);
    estruturas_freeEstruturas(grafo, pilha);
}