/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
// Implementação dos Métodos de Pesquisa Binária e Sequencial. É precisa implementar as duas variações (Recursiva e Estruturada) do método de pesquisa binária.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#define TAMANHO 10

typedef long TChave;

typedef struct{
    TChave Chave;
    int v1[TAMANHO];
}Titem;

typedef struct{
    Titem *v;
    int n, max;
}TDicionario;

// Protótipos das funções
void TDicionario_Inicio(TDicionario *t);
void TDicionario_Insere_Corrigido(TDicionario *t, Titem *x);
void TDicionario_Ordena(TDicionario *t);
int PBinaria_Corrigida(TDicionario *A, TChave x);

void TDicionario_Inicio(TDicionario *t)
{
    t->n = 0;
    t->max = TAMANHO;
    t->v = (Titem*)malloc(sizeof(Titem)*t->max);
}

void TDicionario_Insere_Corrigido(TDicionario *t, Titem *x){
    if(t->n == t->max){
        t->max *= 2;
        t->v = (Titem*)realloc(t->v, sizeof(Titem)*t->max);
    }
    t->v[t->n] = *x; // 1. Insere
    t->n++;          // 2. Incrementa
}

void TDicionario_Ordena(TDicionario *t)
{
    for (int i = 0; i < t->n - 1; i++)
    {
        for (int j = 0; j < t->n - i - 1; j++)
        {
            if (t->v[j].Chave > t->v[j + 1].Chave)
            {
                Titem temp = t->v[j];
                t->v[j] = t->v[j + 1];
                t->v[j + 1] = temp;
            }
        }
    }
}

// VERSÃO CORRIGIDA
int PBinaria_Corrigida(TDicionario *A, TChave x){
    int ie = 0;
    int id = A->n - 1;
    while(ie <= id){
        int m = (ie+id) / 2;
        if(x < A->v[m].Chave)
            id = m - 1;
        else if(x > A->v[m].Chave)
            ie = m+1;
        else
            return m; // Encontrado
    }
    // Se o loop terminar, significa que não encontrou.
    return -1;
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    TDicionario meuDicionario;
    TDicionario_Inicio(&meuDicionario);

    // 1. INSERIR VÁRIOS ITENS COM CHAVES FORA DE ORDEM
    Titem item_temp;
    int vetor_qualquer[TAMANHO] = {0}; // Vetor de exemplo, não importa o conteúdo

    // Copiando o vetor para o item temporário (só precisa fazer uma vez)
    for(int i = 0; i < TAMANHO; i++) item_temp.v1[i] = vetor_qualquer[i];
    
    printf("Inserindo itens com chaves: 101, 55, 203, 12, 88\n");
    item_temp.Chave = 101;
    TDicionario_Insere_Corrigido(&meuDicionario, &item_temp);
    item_temp.Chave = 55;
    TDicionario_Insere_Corrigido(&meuDicionario, &item_temp);
    item_temp.Chave = 203;
    TDicionario_Insere_Corrigido(&meuDicionario, &item_temp);
    item_temp.Chave = 12;
    TDicionario_Insere_Corrigido(&meuDicionario, &item_temp);
    item_temp.Chave = 88;
    TDicionario_Insere_Corrigido(&meuDicionario, &item_temp);

    printf("\nDicionário antes da ordenação:\n");
    for(int i=0; i < meuDicionario.n; i++){
        printf("Índice %d -> Chave: %ld\n", i, meuDicionario.v[i].Chave);
    }

    // 2. ORDENAR O DICIONÁRIO (PASSO CRUCIAL)
    printf("\nOrdenando o dicionário...\n");
    TDicionario_Ordena(&meuDicionario);

    printf("\nDicionário DEPOIS da ordenação:\n");
    for(int i=0; i < meuDicionario.n; i++){
        printf("Índice %d -> Chave: %ld\n", i, meuDicionario.v[i].Chave);
    }

    // 3. REALIZAR A PESQUISA BINÁRIA
    TChave chave_para_buscar = 88;
    printf("\nBuscando pela chave %ld com Pesquisa Binária...\n", chave_para_buscar);

    int indice_encontrado = PBinaria_Corrigida(&meuDicionario, chave_para_buscar);

    // 4. MOSTRAR O RESULTADO
    if (indice_encontrado != -1) {
        printf(">> SUCESSO: Chave %ld encontrada no índice %d.\n", chave_para_buscar, indice_encontrado);
    } else {
        printf(">> FALHA: Chave %ld não foi encontrada.\n", chave_para_buscar);
    }
    
    // Teste com uma chave que não existe
    chave_para_buscar = 999;
    printf("\nBuscando pela chave %ld (que não existe)...\n", chave_para_buscar);
    indice_encontrado = PBinaria_Corrigida(&meuDicionario, chave_para_buscar);
    if (indice_encontrado != -1) {
        printf(">> SUCESSO: Chave %ld encontrada no índice %d.\n", chave_para_buscar, indice_encontrado);
    } else {
        printf(">> FALHA: Chave %ld não foi encontrada, como esperado.\n", chave_para_buscar);
    }
    
    // Liberar memória alocada
    free(meuDicionario.v);

    return 0;
}
