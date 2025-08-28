/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
#include <stdio.h>
#define TAMANHO 6
#include <locale.h>

void Insercao(int A[], int n)
{
    int i,j;
    int x;
    for(i=2; i <= n; i++)
    {
        x = A[i];
        j = i - 1;
        A[0] = x; //Sentinela
        while(x < A[j])
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
}

void imprimirVetor(int v[], int n)
{
    // Função para imprimir os elementos do vetor
    int i;
    for (i = 1; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    // Declaração de variáveis
    int i, v1[TAMANHO] = {0, 8, 4, 1, 7, 3};

    // Exibição dos vetores originais
    printf("O vetor original é: \n");
    imprimirVetor(v1, TAMANHO);

    // Ordenação dos vetores
    Insercao(v1, TAMANHO - 1);

    // Exibição dos resultados
    printf("\nO vetor após a ordenação é: \n");
    imprimirVetor(v1, TAMANHO);

    printf("\nO maior valor do vetor é: %d\n", v1[TAMANHO - 1]); // Usa-se v1[TAMANHO - 1] para printar o maior valor (Acessa a posição 5)
    return 0;
}
