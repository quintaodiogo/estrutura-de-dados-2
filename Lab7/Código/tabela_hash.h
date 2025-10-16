#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "lista.h" // Inclui a definição do nosso TAD de Lista

// --- Estrutura ---

// Estrutura da Tabela Hash
typedef struct TabelaHash {
    int M;             // Tamanho da tabela
    int colisoes;      // Contador de colisões
    Lista** baldes;    // Vetor de ponteiros para listas (nossos "baldes")
} TabelaHash;

// --- Protótipos das Funções ---

/**
 * @brief Cria e inicializa uma Tabela Hash com um tamanho M.
 * @param M O tamanho da tabela (número de posições no vetor).
 * @return Um ponteiro para a Tabela Hash criada.
 */
TabelaHash* criar_tabela(int M);

/**
 * @brief Insere uma chave (string) na tabela hash.
 * Gerencia a conversão da string, o cálculo do hash e a inserção na lista apropriada.
 * Atualiza o contador de colisões interno.
 * @param tabela A tabela onde a chave será inserida.
 * @param chave A string a ser inserida.
 */
void inserir_na_tabela(TabelaHash* tabela, const char* chave);

/**
 * @brief Libera toda a memória alocada para a tabela hash.
 * @param tabela A tabela a ser liberada.
 */
void liberar_tabela(TabelaHash* tabela);

/**
 * @brief (Opcional) Imprime o conteúdo de toda a tabela hash, para depuração.
 * @param tabela A tabela a ser impressa.
 */
void imprimir_tabela(TabelaHash* tabela);


#endif // TABELA_HASH_H