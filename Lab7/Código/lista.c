#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h" 

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
        exit(1); 
    }

    novo_no->string = strdup(valor);
    if (novo_no->string == NULL) {
        perror("Erro ao alocar memoria para a string");
        free(novo_no); 
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
        proximo_no = atual->proximo; 
        free(atual->string);        
        free(atual);                
        atual = proximo_no;         
    }

    free(lista); 
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
