#ifndef HASH_H
#define HASH_H // Isso evita que o compilador inclua este arquivo mais de uma vez

typedef struct No {
    char *chave;
    struct No *proximo;
} No;

typedef struct TabelaHash {
    int tamanho;
    No **tabela;
} TabelaHash;

TabelaHash* criar_tabela(int M);
void tabela_inserir(TabelaHash* th, const char* chave);
void tabela_destruir(TabelaHash* th);
void tabela_imprimir(TabelaHash* th); // A função de visualização
unsigned int funcao_hash(const char *chave, int tamanho_tabela);

#endif