/*Diogo de Paula Quintão e João Pedro da Costa Reis*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 15

void Selecao(int A[], int n)
{
    // Função de ordenação por seleção
    int i, j, Min;
    int x;
    for (i = 0; i <= n - 1; i++)
    {
        Min = i;
        for (j = i + 1; j < n; j++)
        {
            if (A[j] < A[Min])
            {
                Min = j;
            }
        }
        x = A[Min];
        A[Min] = A[i];
        A[i] = x;
    }
}

void printarVetor(int v[])
{
    // Função para imprimir os elementos do vetor
    int i;
    for (i = 0; i < TAMANHO; i++)
    {
        printf(" %d", v[i]);
    }
}

int main()
{
    // Declaração de variáveis
    int i;
    int v1[TAMANHO] = {8, 13, 21, 0, 9, 3, 7, 2, 1, 62, 1, -4, -12, -9, 12};
    int v2[TAMANHO];
    
    // Geração do vetor aleatório
    srand(time(NULL));
    for (i = 0; i < TAMANHO; i++)
    {
        v2[i] = (rand() % 100) + 1;
    }
    
    // Exibição dos vetores originais
    printf("O vetor fixo é: ");
    printarVetor(v1);
    printf("\nO vetor aleatório é: ");
    printarVetor(v2);
    printf("\n");
    
    // Ordenação dos vetores
    Selecao(v1, TAMANHO);
    Selecao(v2, TAMANHO);
    
    // Exibição dos resultados
    printf("\nO vetor fixo ordenado é: ");
    printarVetor(v1);
    printf("\nO menor valor do vetor fixo é: %d", v1[0]);
    
    printf("\n\nO vetor aleatório ordenado é: ");
    printarVetor(v2);
    printf("\nO menor valor do vetor aleatório é: %d\n", v2[0]);

    return 0;
}