/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
#include <stdio.h>
#define TAMANHO 6
#include <locale.h>

void Funcao(int A[], int n)
{
    
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
    Funcao(v1, TAMANHO);

    // Exibição dos resultados
    printf("\nO vetor após a ordenação é: \n");
    imprimirVetor(v1, TAMANHO);

    printf("\nO maior valor do vetor é: %d\n", v1[TAMANHO]);
} 
