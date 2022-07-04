#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct structVertice {
    int indice;
    int cor;
} *PonteiroVertice;

typedef struct structGrafo {
    int id;
    int tamanho;
    int registradoresFisicos;
    int primeiroRegistradorLogico;
    int* registradoresLogicosAlocados;
    int **matrizAdjacencia;
    int **matrizAdjacenciaOriginal;
    PonteiroVertice *vertices;
} *PonteiroGrafo;

typedef struct structPilha {
    int topo;
    PonteiroVertice *vertices;
} *PonteiroPilha;

static int spillStart;

/* Grafo */

Grafo estruturas_criarGrafo(int tamanho) {
    int i;
    int j;

    PonteiroGrafo novoGrafo = malloc(sizeof(struct structGrafo));

    novoGrafo->tamanho = tamanho;

    novoGrafo->vertices = malloc(tamanho * (sizeof(struct structVertice)));

    novoGrafo->registradoresLogicosAlocados = malloc(tamanho * (sizeof(int)));

    novoGrafo->matrizAdjacencia = malloc(tamanho * sizeof(int *));
    for (i = 0; i < tamanho; i++) {
        novoGrafo->matrizAdjacencia[i] = malloc(tamanho * sizeof(int));
    }

    novoGrafo->matrizAdjacenciaOriginal = malloc(tamanho * sizeof(int *));
    for (i = 0; i < tamanho; i++) {
        novoGrafo->matrizAdjacenciaOriginal[i] = malloc(tamanho * sizeof(int));
    }

    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            novoGrafo->matrizAdjacencia[i][j] = 0;
        }
    }

    for (i = 0; i < tamanho; i++) {
        novoGrafo->registradoresLogicosAlocados[i] = 0;
    }

    spillStart = 0;

    return novoGrafo;
}

void estruturas_setIdGrafo(Grafo grafoParametro, int id) {
PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    grafo->id = id;
}

void estruturas_setRegistradoresFisicos(Grafo grafoParametro, int registradoresFisicos) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    grafo->registradoresFisicos = registradoresFisicos;
}

void estruturas_setPrimeiroRegistradorLogico(Grafo grafoParametro, int primeiroRegistradorLogico) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    grafo->primeiroRegistradorLogico = primeiroRegistradorLogico;
}

int estruturas_getPrimeiroRegistradorLogico(Grafo grafoParametro) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->primeiroRegistradorLogico;
}

void estruturas_alterarMatrizAdjacencia(Grafo grafoParametro, int i, int j, int valor) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    grafo->matrizAdjacencia[i][j] = valor;
    grafo->registradoresLogicosAlocados[i] = 1;
}

int **estruturas_getMatrizAdjacencia(Grafo grafoParametro) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->matrizAdjacencia;
}

int estruturas_getTamanhoGrafo(Grafo grafoParametro) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->tamanho;
}

int estruturas_getRegistradoresFisicos(Grafo grafoParametro) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->registradoresFisicos;
}

int **estruturas_getMatrizAdjacenciaOriginal(Grafo grafoParametro) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->matrizAdjacenciaOriginal;
}

void estruturas_setMatrizAdjacenciaOriginal(Grafo grafoParametro) {
    int i;
    int j;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    for (i = 0; i < grafo->tamanho; i++) {
        for (j = 0; j < grafo->tamanho; j++) {
            grafo->matrizAdjacenciaOriginal[i][j] = grafo->matrizAdjacencia[i][j];
        }
    }
}

void estruturas_resetMatrizAdjacencia(Grafo grafoParametro) {
    int i;
    int j;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    for (i = 0; i < grafo->tamanho; i++) {
        for (j = 0; j < grafo->tamanho; j++) {
            grafo->matrizAdjacencia[i][j] = grafo->matrizAdjacenciaOriginal[i][j];
        }
    }
}

Vertice estruturas_getVertice(Grafo grafoParametro, int indice) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->vertices[indice];
}

void estruturas_removerVerticeMatrizAdjacencia(Grafo grafoParametro, int indice) {
    int i;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;

    for(i = 0; i < grafo->tamanho; i++) {
        //grafo->matrizAdjacencia[indice][i] = 0;
        grafo->matrizAdjacencia[i][indice] = 0;
    }
}

void estruturas_removerVerticeMaiorGrau(Grafo grafoParametro, Pilha pilha, int inicio, int tamanho) {
    int i;
    int j;
    int grau;
    int maiorGrau;
    int indiceRemover;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;

    maiorGrau = 0;
    for (i = inicio; i < tamanho; i++) {
        grau = 0;
        for (j = 0; j < tamanho; j++) {
            if (grafo->matrizAdjacencia[i][j] == 1) {
                grau++;
            }
        }
        if (grau > maiorGrau) {
            maiorGrau = grau;
            indiceRemover = i;
        }
    }

    for (i = 0; i < grafo->tamanho; i++) {
        grafo->matrizAdjacencia[indiceRemover][i] = 0;
        grafo->matrizAdjacencia[i][indiceRemover] = 0;
    }

    estruturas_pushPilha(pilha, estruturas_getVertice(grafoParametro, indiceRemover));
    printf("Push: %d *\n", indiceRemover);
}

void estruturas_restaurarVerticeMatrizAdjacencia(Grafo grafoParametro, int indice) {
    int i;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;

    for (i = 0; i < grafo->tamanho; i++) {
        grafo->matrizAdjacencia[indice][i] = grafo->matrizAdjacenciaOriginal[indice][i];
        grafo->matrizAdjacencia[i][indice] = grafo->matrizAdjacenciaOriginal[i][indice];
    }
}

int estruturas_registradorLogicoAlocado(Grafo grafoParametro, int indice) {
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    return grafo->registradoresLogicosAlocados[indice];
}

/* Vertice */

void estruturas_criarInserirVertice(Grafo grafoParametro, int indice, int tamanhoRegistradoresFisicos) {
    int i;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    PonteiroVertice novoVertice = malloc(sizeof(struct structVertice));
    novoVertice->indice = indice;
    grafo->vertices[indice] = novoVertice;
}

/* Pilha */

Pilha estruturas_criarPilha(int tamanhoMaximo) {
    PonteiroPilha novaPilha = malloc(sizeof(struct structPilha));
    novaPilha->vertices = malloc(tamanhoMaximo * (sizeof(struct structVertice)));
    novaPilha->topo = -1;
    return novaPilha;
}

void estruturas_limparPilha(Pilha pilhaParametro) {
    PonteiroPilha pilha = (PonteiroPilha) pilhaParametro;
    pilha->topo = -1;
}

void estruturas_pushPilha(Pilha pilhaParametro, Vertice verticeParametro) {
    PonteiroPilha pilha = (PonteiroPilha) pilhaParametro;
    PonteiroVertice vertice = (PonteiroVertice) verticeParametro;
    pilha->topo++;
    pilha->vertices[pilha->topo] = vertice;
}

int estruturas_isIndiceNaPilha(Pilha pilhaParametro, int indice) {
    int i;
    PonteiroPilha pilha = (PonteiroPilha) pilhaParametro;
    for (i = 0; i < (pilha->topo) + 1; i++) {
        if (pilha->vertices[i]->indice == indice) {
            return 1;
        }
    }
    return 0;
}

void estruturas_popPilha(Pilha pilhaParametro) {
    PonteiroPilha pilha = (PonteiroPilha) pilhaParametro;
    printf("Pop: %d", pilha->vertices[pilha->topo]->indice);
    pilha->topo--;
}

void util_pintar(PonteiroGrafo grafo, int registradorLogico, int cor) {
    int i;
    for(i = grafo->primeiroRegistradorLogico; i < grafo->tamanho; i++) {
        if(grafo->matrizAdjacencia[registradorLogico][i] == 1) {
            grafo->matrizAdjacencia[i][cor] = 1;
        }
    } 
}

void estruturas_desempilhar(Pilha pilhaParametro, Grafo grafoParametro, int cores) {
    int i;
    int j;
    int topo;
    int cor;
    int registradorLogico;
    int flgSpill;
    int flgOperacao;

    PonteiroPilha pilha = (PonteiroPilha) pilhaParametro;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;

    i = 0;

    while(pilha->topo > -1) {
        topo = pilha->vertices[pilha->topo]->indice;
        flgOperacao = 0;
        for(j = 0; j < grafo->registradoresFisicos; j++) {
            cor = j;
            if(grafo->matrizAdjacencia[topo][j] == 0) {
                if(cor >= cores) {
                    if(cores > spillStart) {
                        spillStart = cores;
                    }
                    estruturas_popPilha(pilha);
                    printf(" -> NO COLOR AVAILABLE\n");
                    flgSpill = 1;
                    estruturas_limparPilha(pilhaParametro);
                    flgOperacao = 1;
                } else {
                    registradorLogico = topo;
                    estruturas_popPilha(pilha);
                    printf(" -> %d\n", cor);
                    util_pintar(grafo, registradorLogico, cor);
                    flgOperacao = 1;
                }
                // Exit segundo for
                j = grafo->registradoresFisicos;
            }
        }
        if(flgOperacao == 0) {
            if(cores > spillStart) {
                spillStart = cores;
            }
            estruturas_popPilha(pilha);
            printf(" -> NO COLOR AVAILABLE\n");
            flgSpill = 1;
            estruturas_limparPilha(pilhaParametro);
            flgOperacao = 1;
            j = grafo->registradoresFisicos;
        }
        i++;
    }
}

void estruturas_exibirRelatorio(Grafo grafoParametro) {
    int i;
    int k;
    spillStart++;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    printf("----------------------------------------\n");
    printf("----------------------------------------");
    k = grafo->registradoresFisicos;
    for(i = k; i > 1; i--) {
        printf("\nGraph %d -> K = ", grafo->id);
        if(k < 10) printf(" ");
        printf("%d: ", k);
        if(i < spillStart) {
            printf("SPILL");
        } else {
            printf("Successful Allocation");
        }
        k--;
    }
}

void estruturas_freeEstruturas(Grafo grafoParametro, Pilha pilhaParametro) {
    int i;
    PonteiroGrafo grafo = (PonteiroGrafo) grafoParametro;
    PonteiroPilha pilha = (PonteiroPilha) pilhaParametro;

    PonteiroVertice verticeAuxiliar;
    int* ponteiroIntAuxiliar_1;
    int* ponteiroIntAuxiliar_2;

    for (i = 0; i < pilha->topo + 1; i++) {
        free(pilha->vertices[i]);
    }

    free(pilha->vertices);
    free(pilha);

    for (i = grafo->primeiroRegistradorLogico; i < grafo->tamanho; i++) {
        if(grafo->registradoresLogicosAlocados[i]) {
            verticeAuxiliar = grafo->vertices[i];
            free(verticeAuxiliar);
        }
    }

    for (i = 0; i < grafo->tamanho; i++) {
        ponteiroIntAuxiliar_1 = grafo->matrizAdjacencia[i];
        ponteiroIntAuxiliar_2 = grafo->matrizAdjacenciaOriginal[i];
        free(ponteiroIntAuxiliar_1);
        free(ponteiroIntAuxiliar_2);
    }
    
    free(grafo->matrizAdjacencia);
    free(grafo->matrizAdjacenciaOriginal);

    free(grafo->registradoresLogicosAlocados);

    free(grafo->vertices);
    free(grafo);
}