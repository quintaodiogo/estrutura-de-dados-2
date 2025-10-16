#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Essencial para medir o tempo e para gerar números aleatórios
#include "lista.h"
#include "tabela_hash.h"

// --- Parte 1: Gerador de Strings Aleatórias ---

/**
 * @brief Gera uma string aleatória de um tamanho específico.
 * A string conterá caracteres alfanuméricos (a-z, A-Z, 0-9).
 * @param tamanho O comprimento da string a ser gerada.
 * @return Um ponteiro para a string alocada dinamicamente. Lembre-se de liberá-la!
 */
char* gerar_string_aleatoria(int tamanho) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* resultado = (char*) malloc((tamanho + 1) * sizeof(char));
    if (resultado == NULL) {
        perror("Falha ao alocar string aleatoria");
        exit(1);
    }

    for (int i = 0; i < tamanho; i++) {
        int key = rand() % (sizeof(charset) - 1);
        resultado[i] = charset[key];
    }

    resultado[tamanho] = '\0'; // Adiciona o terminador nulo
    return resultado;
}


// --- Parte 2: Função para Executar um Teste Específico ---

/**
 * @brief Executa um ciclo de teste completo para um dado M e N.
 * Cria a tabela, gera as strings, insere, mede o tempo/colisões e libera a memória.
 * @param M O tamanho da tabela hash.
 * @param N A quantidade de strings a serem inseridas.
 */
void executar_teste(int M, int N) {
    printf("=== INICIANDO TESTE COM M=%d e N=%d ===\n", M, N);

    // 1. Gerar N strings aleatórias (comprimento 10, por exemplo)
    char** strings_teste = (char**) malloc(N * sizeof(char*));
    if (strings_teste == NULL) {
        perror("Falha ao alocar vetor de strings");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        strings_teste[i] = gerar_string_aleatoria(10);
    }

    // 2. Criar a Tabela Hash
    TabelaHash* tabela = criar_tabela(M);

    // 3. Iniciar o cronômetro
    clock_t inicio = clock();

    // 4. Inserir todas as strings na tabela
    for (int i = 0; i < N; i++) {
        inserir_na_tabela(tabela, strings_teste[i]);
    }

    // 5. Parar o cronômetro
    clock_t fim = clock();

    // 6. Calcular o tempo de execução em segundos
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // 7. Imprimir os resultados no formato solicitado
    printf("M=%-5d | N=%-6d | Colisões=%-6d | Tempo de execução=%.6f segundos\n\n",
           M, N, tabela->colisoes, tempo_execucao);

    // 8. Liberar toda a memória alocada para este teste
    liberar_tabela(tabela);
    for (int i = 0; i < N; i++) {
        free(strings_teste[i]);
    }
    free(strings_teste);
}


// --- Parte 3: A Função `main` ---

int main() {
    // Inicializa o gerador de números aleatórios com uma semente baseada no tempo
    // Isso garante que a cada execução do programa, as strings sejam diferentes
    srand(time(NULL));

    // Parâmetros de teste definidos no PDF
    int valores_M[] = {31, 79, 151}; // 
    int num_M = sizeof(valores_M) / sizeof(valores_M[0]);

    int valores_N[] = {100, 1000, 10000}; // 
    int num_N = sizeof(valores_N) / sizeof(valores_N[0]);

    // Executa o teste para cada combinação de M e N
    for (int i = 0; i < num_M; i++) {
        for (int j = 0; j < num_N; j++) {
            executar_teste(valores_M[i], valores_N[j]);
        }
    }

    return 0;
}
