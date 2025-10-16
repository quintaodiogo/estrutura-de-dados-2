#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

// --- Funções Auxiliares ---

// Converte string para inteiro pela soma dos códigos ASCII [cite: 4, 9]
static unsigned long string_to_int(const char* chave) {
    unsigned long soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma;
}

// Aplica a função hash f(x) = (5*x) % M [cite: 3, 9]
static int funcao_hash(unsigned long x, int M) {
    return (5 * x) % M;
}

// --- Implementação das Funções do TAD ---

TabelaHash* criar_tabela(int M) {
    TabelaHash* nova_tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (nova_tabela == NULL) {
        perror("Falha ao alocar TabelaHash");
        exit(1);
    }

    nova_tabela->M = M;
    nova_tabela->colisoes = 0;

    // Aloca memória para o vetor de ponteiros de Lista
    nova_tabela->baldes = (Lista**) malloc(M * sizeof(Lista*));
    if (nova_tabela->baldes == NULL) {
        perror("Falha ao alocar vetor de baldes");
        free(nova_tabela);
        exit(1);
    }

    // Importante: Inicializa cada lista dentro do vetor
    for (int i = 0; i < M; i++) {
        nova_tabela->baldes[i] = criar_lista();
    }

    return nova_tabela;
}

void inserir_na_tabela(TabelaHash* tabela, const char* chave) {
    if (tabela == NULL) return;

    // 1. Converte a string para um inteiro [cite: 4, 9]
    unsigned long valor_int = string_to_int(chave);

    // 2. Calcula o índice usando a função hash [cite: 3, 9]
    int indice = funcao_hash(valor_int, tabela->M);

    // 3. Insere na lista correspondente e verifica se houve colisão
    int colidiu = inserir_na_lista(tabela->baldes[indice], chave);

    // 4. Se a função de inserção da lista retornou 1, incrementa o contador
    if (colidiu) {
        tabela->colisoes++;
    }
}

void liberar_tabela(TabelaHash* tabela) {
    if (tabela == NULL) return;

    // Libera cada lista individualmente
    for (int i = 0; i < tabela->M; i++) {
        liberar_lista(tabela->baldes[i]);
    }

    // Libera o vetor de ponteiros
    free(tabela->baldes);

    // Libera a estrutura da tabela
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