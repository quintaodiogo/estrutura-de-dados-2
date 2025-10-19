/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
//Implementação Árvores AVL (Enviar código fonte).
//O código fonte deste trabalho deve apresentar a funcionalidade de inserção mantendo as restrições de AVL com as operações de rotação simples e  dupla nos dois sentidos (esquerda e direita).
//Usar como testes os exemplos colocados na transparëncia (https://turing.inf.ufg.br/mod/resource/view.php?id=63278).

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *esq;
    struct Node *dir;
} Node;

// Criação de novo nó
Node* novoNo(int valor) {
    Node* novo = (Node*) malloc(sizeof(Node));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Inserção normal de árvore binária
Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) return novoNo(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

// Altura da árvore
int altura(Node* raiz) {
    if (raiz == NULL) return 0;
    int he = altura(raiz->esq);
    int hd = altura(raiz->dir);
    return (he > hd ? he : hd) + 1;
}

// Impressão da árvore "de lado"
void imprimir(Node* raiz, int nivel) {
    if (raiz == NULL) return;
    imprimir(raiz->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d(h=%d)\n", raiz->valor, altura(raiz));
    imprimir(raiz->esq, nivel + 1);
}

// Rotações AVL
Node* rotacaoEsquerda(Node* p) {
    Node* q = p->dir;
    Node* temp = q->esq;
    q->esq = p;
    p->dir = temp;
    return q;
}

Node* rotacaoDireita(Node* p) {
    Node* q = p->esq;
    Node* temp = q->dir;
    q->dir = p;
    p->esq = temp;
    return q;
}

// Caso 1 - Rotação simples à esquerda
void caso1() {
    printf("\n===== CASO 1: Rotação simples à esquerda =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4);
    raiz->dir = novoNo(10);
    raiz->dir->esq = novoNo(9);
    raiz->dir->dir = novoNo(15);
    raiz->dir->dir->esq = novoNo(12);

    printf("\nÁrvore antes da rotação:\n");
    imprimir(raiz, 0);

    raiz = rotacaoEsquerda(raiz);

    printf("\nÁrvore após rotação à esquerda:\n");
    imprimir(raiz, 0);
}

// Caso 2 - Rotação dupla (esquerda em 4, depois direita em 8)
void caso2() {
    printf("\n===== CASO 2: Rotação dupla (Esq em 4, Dir em 8) =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4);
    raiz->dir = novoNo(10);
    raiz->esq->esq = novoNo(2);
    raiz->esq->dir = novoNo(6);
    raiz->esq->dir->esq = novoNo(5);

    printf("\nÁrvore antes das rotações:\n");
    imprimir(raiz, 0);

    // Rotação à esquerda no nó 4
    raiz->esq = rotacaoEsquerda(raiz->esq);
    // Rotação à direita no nó 8
    raiz = rotacaoDireita(raiz);

    printf("\nÁrvore após as rotações:\n");
    imprimir(raiz, 0);
}

// Caso 3 - Rotação simples à direita
void caso3() {
    printf("\n===== CASO 3: Rotação simples à direita =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4);
    raiz->dir = novoNo(10);
    raiz->esq->esq = novoNo(2);
    raiz->esq->dir = novoNo(6);
    raiz->esq->esq->dir = novoNo(5);

    printf("\nÁrvore antes da rotação:\n");
    imprimir(raiz, 0);

    // Rotação simples à direita no nó 8
    raiz = rotacaoDireita(raiz);

    printf("\nÁrvore após rotação à direita:\n");
    imprimir(raiz, 0);
}

// Caso 4 - Rotação dupla (direita em 4, depois esquerda em 8)
void caso4() {
    printf("\n===== CASO 2: Rotação dupla (Dir em 4, Esq em 8) =====\n");
    Node* raiz = novoNo(8);
    raiz->dir = novoNo(4);
    raiz->esq = novoNo(10);
    raiz->dir->dir = novoNo(2);
    raiz->dir->esq = novoNo(6);
    raiz->dir->esq->dir = novoNo(5);

    printf("\nÁrvore antes das rotações:\n");
    imprimir(raiz, 0);

    // Rotação à direita no nó 4
    raiz->dir = rotacaoDireita(raiz->esq);
    // Rotação à direita no nó 8
    raiz = rotacaoEsquerda(raiz);

    printf("\nÁrvore após as rotações:\n");
    imprimir(raiz, 0);
}

int main() {
    caso1();
    caso2();
    caso3();
    caso4();
    return 0;
}
