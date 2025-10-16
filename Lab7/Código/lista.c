#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h" // Inclui nossas próprias definições

// Implementação das funções

Lista* criar_lista() {
    Lista* nova_lista = (Lista*) malloc(sizeof(Lista));
    if (nova_lista != NULL) {
        nova_lista->cabeca = NULL; // Uma lista nova sempre começa vazia
    }
    return nova_lista;
}

int inserir_na_lista(Lista* lista, const char* valor) {
    if (lista == NULL) return 0;

    // A lista já tem elementos? Se sim, isso conta como uma colisão na tabela hash.
    int colidiu = (lista->cabeca != NULL);

    // Cria o novo nó
    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        exit(1); // Em um programa real, tratar o erro de forma mais elegante.
    }

    // Aloca memória para a string e a copia. Usamos strdup para isso.
    // strdup = string duplicate (aloca memória e copia a string).
    novo_no->string = strdup(valor);
    if (novo_no->string == NULL) {
        perror("Erro ao alocar memoria para a string");
        free(novo_no); // Libera o nó alocado
        exit(1);
    }

    // Insere o novo nó no início da lista
    novo_no->proximo = lista->cabeca;
    lista->cabeca = novo_no;

    return colidiu;
}

void liberar_lista(Lista* lista) {
    if (lista == NULL) return;

    No* atual = lista->cabeca;
    No* proximo_no;

    while (atual != NULL) {
        proximo_no = atual->proximo; // Guarda a referência para o próximo
        free(atual->string);        // Libera a string duplicada
        free(atual);                // Libera o nó atual
        atual = proximo_no;         // Move para o próximo
    }

    free(lista); // Libera a estrutura da lista
}

void imprimir_lista(Lista* lista) {
    if (lista == NULL) return;

    No* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%s -> ", atual->string);
        atual = atual->proximo;
    }
    printf("NULL\n");
}