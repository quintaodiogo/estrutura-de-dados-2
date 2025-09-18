/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
// Implementação do Método de Ordenação do Bubble Sort Melhorado (usando a variável booleana)

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#define TAMANHO 10


void bubbleSort(int A[], int n)
{
    int i, j, aux;
    bool troca = true;
    for (i = n - 1; i >= 1 && troca; i--)
    {
        troca = false; // Inicializa a variável booleana como falso (0)
        for (j = 0; j < i; j++)
        {
            if (A[j] > A[j + 1])
            {
                aux = A[j];
                A[j] = A[j + 1];
                A[j + 1] = aux;
                troca = true; // Define a variável booleana como verdadeiro (1) se uma troca ocorrer
            }
        }
    }
}

// Função para imprimir os elementos do vetor
void imprimirVetor(int v[], int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_ALL, "Portuguese");
    // Declaração de variáveis
    int v1[TAMANHO] = {3, 0, 1, 8, 7, 2, 5, 4, 9, 6};

    // Exibição dos vetores originais
    printf("O vetor original é: ");
    imprimirVetor(v1, TAMANHO);

    // Ordenação do vetor utilizando Bubble Sort
    bubbleSort(v1, TAMANHO);

    // Exibição dos vetores ordenados
    printf("O vetor ordenado é: ");
    imprimirVetor(v1, TAMANHO);

    return 0;
}