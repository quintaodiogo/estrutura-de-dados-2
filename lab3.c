/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/

/*Implementação do Método de Ordenação Shellsort, seguindo a sequência de Knuth (h=(h*3)+1).
Imprimir o vetor para cada sequência de h-ordenado.*/
#include <stdio.h>
#define TAMANHO 5
#include <locale.h>

void shellSort(int A[], int n)
{
    int i, j, h, temp;
    h = 1;
    while (h < n)
    {
        h = (h * 3) + 1;
    }
    while (h > 0)
    {
        h /= 3;
        for (i = h; i < n; i++)
        {
            temp = A[i];
            j = i - h;
            while (j >= 0 && temp < A[j])
            {
                A[j + h] = A[j];
                j -= h;
            }
            A[j + h] = temp;
        }
        printf("Vetor h-ordenado para h = %d: ", A);
        imprimirVetor(A, n);
    }
}

void imprimirVetor(int v[], int n)
{
    // Função para imprimir os elementos do vetor
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    // Declaração de variáveis
    int i, v1[TAMANHO] = {8, 4, 1, 7, 3};

    // Exibição dos vetores originais
    printf("O vetor original é: \n");
    imprimirVetor(v1, TAMANHO);

    // Ordenação dos vetores
    shellSort(v1, TAMANHO);
}
