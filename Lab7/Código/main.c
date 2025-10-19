/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
//–Implementar uma função hash simples que recebe strings como entrada e usa a estrutura de lista linear para tratar colisões.
//–Use M como 31, 79, 151.
//–Entrada: 100, 1000, 10000 strings.
//–Saída: Elabore gráficos 2D (por exemplo, planilha Excel, Google sheets, etc)  para diferentes medidas: Número de colisões e tempo de execução (Pesquisar dados), usando média de 10 testes por ponto do gráfico.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <locale.h>
#include "lista.h"
#include "tabela_hash.h"

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
    resultado[tamanho] = '\0'; 
    return resultado;
}

void executar_teste(int M, int N) {
    printf("=== INICIANDO TESTE COM M=%d e N=%d ===\n", M, N);
    char** strings_teste = (char**) malloc(N * sizeof(char*));
    if (strings_teste == NULL) {
        perror("Falha ao alocar vetor de strings");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        strings_teste[i] = gerar_string_aleatoria(10);
    }
    TabelaHash* tabela = criar_tabela(M);
    clock_t inicio = clock();
    for (int i = 0; i < N; i++) {
        inserir_na_tabela(tabela, strings_teste[i]);
    }
    clock_t fim = clock();
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("M=%-5d | N=%-6d | Colisões=%-6d | Tempo de execução=%.6f segundos\n\n", M, N, tabela->colisoes, tempo_execucao);
    liberar_tabela(tabela);
    for (int i = 0; i < N; i++) {
        free(strings_teste[i]);
    }
    free(strings_teste);
}



int main() {
    setlocale(LC_ALL, "Portuguese");
    
    srand(time(NULL));
    int valores_M[] = {31, 79, 151};  
    int num_M = sizeof(valores_M) / sizeof(valores_M[0]);
    int valores_N[] = {100, 1000, 10000};  
    int num_N = sizeof(valores_N) / sizeof(valores_N[0]);

    for (int i = 0; i < num_M; i++) {
        for (int j = 0; j < num_N; j++) {
            executar_teste(valores_M[i], valores_N[j]);
        }
    }
    return 0;
}
