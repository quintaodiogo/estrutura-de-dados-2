/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/

#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stdbool.h>

// Definição da Ordem da Árvore B
#define M 5

typedef struct BTreeNode {
    // Vetores com margem de segurança (+1) para operações de split/merge
    int chaves[M];          
    struct BTreeNode *filhos[M + 1]; 
    int n;                  
    bool folha;             
} BTreeNode;

// Funções de Gerenciamento
BTreeNode* criarNo(bool folha);
void liberarArvore(BTreeNode* raiz); // Adicionei aqui pois é útil ser pública

// Funções de Operação
void imprimirArvore(BTreeNode* raiz, int nivel, bool usar_letras); 
BTreeNode* buscarChave(BTreeNode* raiz, int k);
void inserir(BTreeNode** raiz, int k);
void remover(BTreeNode** raiz, int k);

#endif

