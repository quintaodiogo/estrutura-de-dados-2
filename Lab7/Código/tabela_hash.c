#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

static unsigned long string_to_int(const char* chave) {
    unsigned long soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma;
}

static int funcao_hash(unsigned long x, int M) {
    return (5 * x) % M;
}

TabelaHash* criar_tabela(int M) {
    TabelaHash* nova_tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (nova_tabela == NULL) {
        perror("Falha ao alocar TabelaHash");
        exit(1);
    }
    nova_tabela->M = M;
    nova_tabela->colisoes = 0;
    nova_tabela->baldes = (Lista**) malloc(M * sizeof(Lista*));
    if (nova_tabela->baldes == NULL) {
        perror("Falha ao alocar vetor de baldes");
        free(nova_tabela);
        exit(1);
    }
    for (int i = 0; i < M; i++) {
        nova_tabela->baldes[i] = criar_lista();
    }
    return nova_tabela;
}

void inserir_na_tabela(TabelaHash* tabela, const char* chave) {
    if (tabela == NULL) return;
    unsigned long valor_int = string_to_int(chave);
    int indice = funcao_hash(valor_int, tabela->M);
    int colidiu = inserir_na_lista(tabela->baldes[indice], chave);
    if (colidiu) {
        tabela->colisoes++;
    }
}

void liberar_tabela(TabelaHash* tabela) {
    if (tabela == NULL) return;
    for (int i = 0; i < tabela->M; i++) {
        liberar_lista(tabela->baldes[i]);
    }
    free(tabela->baldes);
    free(tabela);
}

void imprimir_tabela(TabelaHash* tabela) {
    if (tabela == NULL) return;
    printf("--- TABELA HASH (M=%d) ---\n", tabela->M);
    for (int i = 0; i < tabela->M; i++) {
        printf("[%03d]: ", i);
        imprimir_lista(tabela->baldes[i]);
    }
    printf("---------------------------\n");
}
