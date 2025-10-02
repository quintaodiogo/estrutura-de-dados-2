//Criar uma função para as palavras desejadas
//Criar a estrutura da função Hash propriamente dita 
//Criar a função de cálculo da Hash

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

unsigned int funcao_hash(const char *chave, int tamanho_tabela){
    unsigned long int hash = 5381;
    int c;

    while((c = *chave++)){
        hash = ((hash <<5) + hash) + c;
    }
    return hash % tamanho_tabela;
}

TabelaHash* criar_tabela(int M){
    TabelaHash *th = (TabelaHash*) malloc(sizeof(TabelaHash));
    if(th == NULL){
        return NULL;
    }
    th->tamanho = M;

    th->tabela = (No**) calloc(M, sizeof(No*));
    if (th->tabela == NULL) {
        // Se a alocação do array falhar, libera o que já foi alocado
        free(th);
        return NULL;
    }

    return th;
}

void tabela_inserir(TabelaHash* th, const char* chave) {
    if (th == NULL) return;

    // 1. Calcula o índice
    int indice = funcao_hash(chave, th->tamanho);

    // 2. Cria um novo nó
    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) return; // Verificação de falha
    novo_no->chave = strdup(chave);
    if (novo_no->chave == NULL) { // Verificação de falha
        free(novo_no);
        return;
    }

    // 3. Insere o nó no início da lista
    novo_no->proximo = th->tabela[indice];
    th->tabela[indice] = novo_no;
}

void tabela_destruir(TabelaHash* th) {
    if (th == NULL) return;

    // Itera sobre cada bucket da tabela
    for (int i = 0; i < th->tamanho; i++) {
        No* no_atual = th->tabela[i];
        // Percorre a lista encadeada liberando cada nó
        while (no_atual != NULL) {
            No* no_temporario = no_atual;
            no_atual = no_atual->proximo;

            free(no_temporario->chave); // Libera a string copiada
            free(no_temporario);      // Libera o nó
        }
    }
    free(th->tabela); 
    free(th);        
}

void tabela_imprimir(TabelaHash* th) {
    printf("--- Estado da Tabela Hash ---\n");
    for (int i = 0; i < th->tamanho; i++) {
        printf("Indice [%d]: ", i);
        No* no_atual = th->tabela[i];
        if (no_atual == NULL) {
            printf("Vazio\n");
        } else {
            while (no_atual != NULL) {
                printf("%s -> ", no_atual->chave);
                no_atual = no_atual->proximo;
            }
            printf("NULL\n");
        }
    }
    printf("-----------------------------\n");
}