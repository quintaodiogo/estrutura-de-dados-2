/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
// Implementação dos Métodos de Pesquisa Sequencial. 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#define TAMANHO 10

typedef long TChave;

typedef struct
{
    TChave Chave;
    int v1[TAMANHO];
} TItem;

typedef struct
{
    TItem *v;
    int n, max;
} TDicionario;

// Inicializar dicionário
void TDicionario_Inicio(TDicionario *t)
{
    t->n = 0;
    t->max = TAMANHO;
    t->v = (TItem *)malloc(sizeof(TItem) * t->max);
}

// Insere um registro no dicionário 
void TDicionario_Insere(TDicionario *t, TItem *x)
{
    if (t->n == t->max)
    {
        t->max *= 2;
        t->v = (TItem *)realloc(t->v, sizeof(TItem) * t->max);
    }
    t->v[t->n] = *x; // Inserir no índice t->n
    t->n++;         // Depois incrementar n
}

// Deleta um registro no dicionário
void TDicionario_Deleta(TDicionario *t, TChave chave) {
    int i, j;
    for (i = 0; i < t->n; i++) {
        if (t->v[i].Chave == chave) {
            for (j = i; j < t->n - 1; j++) {
                t->v[j] = t->v[j + 1];
            }
            t->n--;
            return;
        }
    }
}

//Pesquisa Sequencial 
int PSequencial(TDicionario *A, TChave x)
{
    int i;
    for (i = 0; i < A->n; i++)
    {
        if (A->v[i].Chave == x)
        {
            return i;
        }
    }
    return -1; // retorna -1 caso a chave não seja encontrada.
}
// Função para imprimir os elementos de um vetor
void imprimirVetor(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// Função para imprimir o dicionário
void TDicionario_Imprime(TDicionario *t)
{
    printf("Dicionário (%d elementos):\n", t->n);
    for (int i = 0; i < t->n; i++)
    {
        printf("  [%d] Chave: %ld, Vetor: ", i, t->v[i].Chave);
        imprimirVetor(t->v[i].v1, TAMANHO);
    }
} 

// Função para liberar memória do dicionário
void TDicionario_Libera(TDicionario *t)
{
    free(t->v);
    t->v = NULL;
    t->n = 0;
    t->max = 0;
}

// Função auxiliar para criar um TItem
TItem TItem_Cria(TChave chave, int vetor[])
{
    TItem item;
    item.Chave = chave;
    for (int i = 0; i < TAMANHO; i++)
    {
        item.v1[i] = vetor[i];
    }
    return item;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Portuguese");
    // Declaração de variáveis
    int v1[TAMANHO] = {3, 0, 1, 8, 7, 2, 5, 4, 9, 6};

    TDicionario dicionario1;
    TDicionario_Inicio(&dicionario1);

    // Criar e inserir vários itens no dicionário
    TItem item1 = TItem_Cria(10, v1);
    TItem item2 = TItem_Cria(5, v1);
    TItem item3 = TItem_Cria(15, v1);
    TItem item4 = TItem_Cria(3, v1);
    TItem item5 = TItem_Cria(20, v1);

    TDicionario_Insere(&dicionario1, &item1);
    TDicionario_Insere(&dicionario1, &item2);
    TDicionario_Insere(&dicionario1, &item3);
    TDicionario_Insere(&dicionario1, &item4);
    TDicionario_Insere(&dicionario1, &item5);

    printf("=== DICIONÁRIO INICIAL ===\n");
    TDicionario_Imprime(&dicionario1);

    // Testar pesquisa sequencial - casos diversos
    printf("\n=== TESTE PESQUISA SEQUENCIAL ===\n");
    
    // Teste 1: Buscar primeira chave
    int pos = PSequencial(&dicionario1, 10);
    printf("Buscando chave 10: %s (posição %d)\n", 
           pos != -1 ? "ENCONTRADA" : "NÃO ENCONTRADA", pos);
    
    // Teste 2: Buscar chave do meio
    pos = PSequencial(&dicionario1, 15);
    printf("Buscando chave 15: %s (posição %d)\n", 
           pos != -1 ? "ENCONTRADA" : "NÃO ENCONTRADA", pos);
    
    // Teste 3: Buscar última chave
    pos = PSequencial(&dicionario1, 20);
    printf("Buscando chave 20: %s (posição %d)\n", 
           pos != -1 ? "ENCONTRADA" : "NÃO ENCONTRADA", pos);
    
    // Teste 4: Buscar chave inexistente
    pos = PSequencial(&dicionario1, 99);
    printf("Buscando chave 99: %s (posição %d)\n", 
           pos != -1 ? "ENCONTRADA" : "NÃO ENCONTRADA", pos);

    // Testar deleção
    printf("\n=== TESTE DELEÇÃO ===\n");
    printf("Deletando chave 10...\n");
    TDicionario_Deleta(&dicionario1, 10);
    TDicionario_Imprime(&dicionario1);

    // Liberar memória
    TDicionario_Libera(&dicionario1);

    return 0;
}
