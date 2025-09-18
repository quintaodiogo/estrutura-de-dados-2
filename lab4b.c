/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
/*2) Implementação do método QuickSort conforme video apresentado em aula (https://www.youtube.com/watch?v=ywWBy6J5gz8&embeds_referring_euri=https%3A%2F%2Fturing.inf.ufg.br%2F&embeds_referring_origin=https%3A%2F%2Fturing.inf.ufg.br)*/

#include <stdio.h>
#include <locale.h>
#define TAMANHO 10

int particao(int A[], int esq, int dir) {
    int pivo = A[esq];
    while (esq < dir) {
        // 1. Busca da DIREITA para a ESQUERDA
        while (esq < dir && A[dir] >= pivo) {
            dir--;
        }
        if (esq < dir) {
            A[esq] = A[dir];
            esq++;
        }

        // 2. Busca da ESQUERDA para a DIREITA
        while (esq < dir && A[esq] <= pivo) {
            esq++;
        }
        if (esq < dir) {
            A[dir] = A[esq];
            dir--;
        }
    }
    A[esq] = pivo;
    return esq;
}

void ordena(int A[], int esq, int dir) {
    if (esq < dir) {
        int indice_pivo = particao(A, esq, dir);
        ordena(A, esq, indice_pivo - 1);
        ordena(A, indice_pivo + 1, dir);
    }
}

void quickSort(int A[], int n) {
    ordena(A, 0, n - 1);
}

// Função para imprimir os elementos do vetor
void imprimirVetor(int v[], int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    // Declaração de variáveis
    int v1[TAMANHO] = {3, 0, 1, 8, 7, 2, 5, 4, 9, 6};

    // Exibição dos vetores originais
    printf("O vetor original é: ");
    imprimirVetor(v1, TAMANHO);

    // Ordenação do vetor utilizando Quick Sort
    quickSort(v1, TAMANHO);

    // Exibição dos vetores ordenados
    printf("O vetor ordenado é: ");
    imprimirVetor(v1, TAMANHO);

    return 0;
}
