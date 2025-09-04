/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/

/*1) Implementação do método QuickSort conforme descrição nos slides do moodle (https://turing.inf.ufg.br/mod/resource/view.php?id=63103) e no livro "Projeto de Algoritmos com implementações em Java e C++"*/
#include <stdio.h>
#define TAMANHO 6
#include <locale.h>

void particao(int esq, int dir, int *i, int *j, int A[])
{
    int pivo, aux;
    *i = esq;
    *j = dir;
    pivo = A[(*i + *j) / 2]; //pivo é o elemento central do vetor
    do
    {
        while (pivo > A[*i]) 
            (*i)++;
        while (pivo < A[*j]) 
            (*j)--;
        if (*i <= *j)
        {
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void ordena(int esq, int dir, int A[])
{
    int i, j;
    particao(esq, dir, &i, &j, A);
    if (esq < j) ordena(esq, j, A);
    if (i < dir) ordena(i, dir, A);
}

void quickSort(int A[], int n)
{
    ordena(0, n -1, A);
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
    int i, v1[TAMANHO] = {8, 9, 4, 1, 7, 3};

    // Exibição dos vetores originais
    printf("O vetor original é: ");
    imprimirVetor(v1, TAMANHO);

    // Ordenação dos vetores
    quickSort(v1, TAMANHO);

    // Exibição dos vetores ordenados
    printf("O vetor ordenado é: ");
    imprimirVetor(v1, TAMANHO);

    return 0;
}
