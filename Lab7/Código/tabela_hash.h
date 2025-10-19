#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "lista.h" 

typedef struct TabelaHash {
    int M;             // Tamanho da tabela
    int colisoes;      // Contador de colisões
    Lista** baldes;    // Vetor de ponteiros para listas (nossos "baldes")
} TabelaHash;

TabelaHash* criar_tabela(int M);

void inserir_na_tabela(TabelaHash* tabela, const char* chave);
void liberar_tabela(TabelaHash* tabela);
void imprimir_tabela(TabelaHash* tabela);

#endif 
