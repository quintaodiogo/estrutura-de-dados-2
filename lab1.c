/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
#include <stdio.h>
#define TAMANHO 6
#include <locale.h>

void Selecao(int A[], int n)
{
    // Função de ordenação por seleção
    int i, j, Min;
    int x;
    for (i = 0; i < n - 1; i++)
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

void printarVetor(int v[], int n)
{
    // Função para imprimir os elementos do vetor
    int i;
    for (i = 0; i < n; i++)
    {
        printf(" %d", v[i]);
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    // Declaração de variáveis
    int i, v1[TAMANHO] = {8, 4, 1, 7, 3, 1};
    
    // Exibição dos vetores originais
    printf("O vetor original é: \n");
    printarVetor(v1, TAMANHO);
    
    // Ordenação dos vetores
    Selecao(v1, TAMANHO);
    
    // Exibição dos resultados
    printf("\nO vetor após a ordenação é: \n");
    printarVetor(v1, TAMANHO);
    printf("\nO menor valor do vetor fixo é: %d\n", v1[0]); //Usa-se v1[0] para printar o menor valor pois o vetor
                                                            //já está ordenado de forma crescente.
    return 0;
}
