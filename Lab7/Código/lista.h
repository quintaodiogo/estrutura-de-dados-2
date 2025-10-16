#ifndef LISTA_H
#define LISTA_H

// --- Estruturas ---

// Estrutura do Nó da lista
// Cada nó armazena uma string e um ponteiro para o próximo nó.
typedef struct No {
    char* string;
    struct No* proximo;
} No;

// Estrutura da Lista
// Contém apenas um ponteiro para o primeiro nó (a cabeça da lista).
typedef struct Lista {
    No* cabeca;
} Lista;

// --- Protótipos das Funções ---

/**
 * @brief Aloca memória e inicializa uma nova lista vazia.
 * @return Um ponteiro para a nova lista criada.
 */
Lista* criar_lista();

/**
 * @brief Insere uma nova string no início da lista.
 * @param lista A lista onde a string será inserida.
 * @param valor A string a ser inserida.
 * @return Retorna 1 se a inserção gerou uma colisão (lista não estava vazia), 0 caso contrário.
 */
int inserir_na_lista(Lista* lista, const char* valor);

/**
 * @brief Libera toda a memória associada a uma lista, incluindo todos os seus nós e as strings.
 * @param lista A lista a ser liberada.
 */
void liberar_lista(Lista* lista);

/**
 * @brief (Opcional) Imprime os elementos da lista, útil para depuração.
 * @param lista A lista a ser impressa.
 */
void imprimir_lista(Lista* lista);

#endif // LISTA_H