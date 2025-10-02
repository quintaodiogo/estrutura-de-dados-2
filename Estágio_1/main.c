#include <stdio.h>
#include "hash.h" // Inclui todas as suas declarações de Tabela Hash

int main() {
    // 1. AQUI ESTÃO AS "PALAVRAS DESEJADAS"
    // Elas são apenas um array de strings.
    const char* palavras[] = {
        "banana", "abacaxi", "laranja", "uva", "manga",
        "morango", "cereja", "abacate", "limao", "melancia"
    };
    int num_palavras = 10;
    int M = 10; // O tamanho da tabela que você pediu no exemplo

    printf("Criando tabela hash com tamanho M = %d\n", M);
    TabelaHash* minha_tabela = criar_tabela(M);

    // Verificando se a tabela foi criada com sucesso
    if (minha_tabela == NULL) {
        printf("Erro ao criar a tabela hash.\n");
        return 1;
    }

    printf("\nInserindo palavras na tabela...\n");
    for (int i = 0; i < num_palavras; i++) {
        printf("Inserindo: %s\n", palavras[i]);
        tabela_inserir(minha_tabela, palavras[i]);
    }

    // Imprimindo o resultado para ver as colisões
    printf("\n");
    tabela_imprimir(minha_tabela);

    // Liberando a memória no final
    tabela_destruir(minha_tabela);
    printf("Tabela destruida com sucesso.\n");

    return 0;
}