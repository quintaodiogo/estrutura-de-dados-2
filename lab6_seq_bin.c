/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
// Implementação dos Métodos de Pesquisa Binária e Sequencial. É precisa implementar as duas variações (Recursiva e Estruturada) do método de pesquisa binária.

#include <stdio.h>
#include <stdlib.h>

typedef long TChave;

typedef struct {
    TChave chave; 
} TItem;

typedef struct {
    TItem *v; /* 0..n-1 */
    int n;    /* número de itens válidos */
    int max;  /* capacidade do vetor */
} TDicionario;

/* inicializa um dicionário */
void TDicionario_Inicio(TDicionario *t) {
    t->n = 0;
    t->max = 10;
    t->v = (TItem*) malloc(sizeof(TItem) * t->max);
    if (!t->v) {
        fprintf(stderr, "Erro: malloc\n");
        exit(EXIT_FAILURE);
    }
}

/* insere um registro no dicionário (0-based) */
void TDicionario_Insere(TDicionario *t, TItem *x) {
    if (t->n == t->max) {
        t->max *= 2;
        t->v = (TItem*) realloc(t->v, sizeof(TItem) * t->max);
        if (!t->v) {
            fprintf(stderr, "Erro: realloc\n");
            exit(EXIT_FAILURE);
        }
    }
    t->v[t->n] = *x; /* coloca em v[n] */
    t->n++;          /* aumenta n */
}

/* Pesquisa sequencial simples (0..n-1) */
int PSequencial(TDicionario *A, TChave x) {
    for (int i = 0; i < A->n; i++) {
        if (A->v[i].chave == x) return i;
    }
    return -1; /* não encontrado */
}

/* Bubble Sort */
void BubbleSort(TDicionario *A) {
    if (A->n <= 1) return;
    for (int i = 0; i < A->n - 1; i++) {
        for (int j = 0; j < A->n - 1 - i; j++) {
            if (A->v[j].chave > A->v[j+1].chave) {
                TItem tmp = A->v[j];
                A->v[j] = A->v[j+1];
                A->v[j+1] = tmp;
            }
        }
    }
}

/* Pesquisa Binária Estruturada (iterativa) */
int PBinaria(TDicionario *A, TChave x) {
    int n = A->n;
    int ie = 0;
    int id = n - 1;
    while (ie <= id) {
        int m = (ie + id) / 2;
        if (x < A->v[m].chave)
            id = m - 1;
        else if (x > A->v[m].chave)
            ie = m + 1;
        else /* x == A->v[m].chave */
            return m;
    }
    return -1;
}

/* Pesquisa Binária Recursiva */
int PBinaria_Recursiva(TDicionario *A, int ie, int id, TChave x) {
    if (ie > id) return -1; /* base: intervalo inválido -> não encontrou */
    int meio = (ie + id) / 2;
    if (A->v[meio].chave == x)
        return meio;
    else if (x > A->v[meio].chave)
        return PBinaria_Recursiva(A, meio + 1, id, x);
    else /* x < A->v[meio].chave */
        return PBinaria_Recursiva(A, ie, meio - 1, x);
}

int PBinaria_recursivaExec(TDicionario *A, TChave x) {
    return PBinaria_Recursiva(A, 0, A->n - 1, x);
}

/* imprime chaves 0..n-1 */
void imprime(TDicionario *A) {
    for (int i = 0; i < A->n; i++) {
        printf("%ld ", A->v[i].chave);
    }
    printf("\n");
}

int main(void) {
    TDicionario dic;
    TDicionario_Inicio(&dic);

    /* Vetor de 10 inteiros desordenados */
    long dados[10] = {34, 7, 23, 32, 5, 62, 31, 4, 18, 50};
    TItem it;
    for (int i = 0; i < 10; i++) {
        it.chave = dados[i];
        TDicionario_Insere(&dic, &it);
    }

    printf("Vetor (desordenado): ");
    imprime(&dic);

    TChave chave = 31;
    int pos_seq = PSequencial(&dic, chave);
    if (pos_seq >= 0)
        printf("Pesquisa Sequencial: chave %ld encontrada em posicao %d (no vetor desordenado)\n", chave, pos_seq);
    else
        printf("Pesquisa Sequencial: chave %ld NAO encontrada (no vetor desordenado)\n", chave);

    /* Ordenando antes de executar as pesquisas binárias */
    BubbleSort(&dic);
    printf("Vetor (apos BubbleSort): ");
    imprime(&dic);

    int pos_bin_iter = PBinaria(&dic, chave);
    if (pos_bin_iter >= 0)
        printf("Pesquisa Binaria (iterativa): chave %ld encontrada em posicao %d\n", chave, pos_bin_iter);
    else
        printf("Pesquisa Binaria (iterativa): chave %ld NAO encontrada\n", chave);

    int pos_bin_rec = PBinaria_recursivaExec(&dic, chave);
    if (pos_bin_rec >= 0)
        printf("Pesquisa Binaria (recursiva): chave %ld encontrada em posicao %d\n", chave, pos_bin_rec);
    else
        printf("Pesquisa Binaria (recursiva): chave %ld NAO encontrada\n", chave);

    free(dic.v);
    return 0;
}
