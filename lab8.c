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
    int altura;
} Node;

// Retorna a altura do nó
int altura(Node* n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

// Retorna o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Cria um novo nó
Node* novoNo(int valor) {
    Node* novo = (Node*) malloc(sizeof(Node));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;
    return novo;
}

// Rotação à direita
Node* rotacaoDireita(Node* y) {
    printf("  -> Rotação à direita no nó %d\n", y->valor);
    Node* x = y->esq;
    Node* T2 = x->dir;
    
    x->dir = y;
    y->esq = T2;
    
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    
    return x;
}

// Rotação à esquerda
Node* rotacaoEsquerda(Node* x) {
    printf("  -> Rotação à esquerda no nó %d\n", x->valor);
    Node* y = x->dir;
    Node* T2 = y->esq;
    
    y->esq = x;
    x->dir = T2;
    
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    
    return y;
}

// Calcula o fator de balanceamento
int getBalance(Node* n) {
    if (n == NULL)
        return 0;
    return altura(n->esq) - altura(n->dir);
}

// Inserção com balanceamento automático
Node* inserir(Node* node, int valor) {
    // 1. Inserção normal BST
    if (node == NULL)
        return novoNo(valor);
    
    if (valor < node->valor)
        node->esq = inserir(node->esq, valor);
    else if (valor > node->valor)
        node->dir = inserir(node->dir, valor);
    else
        return node; // Valores duplicados não são permitidos
    
    // 2. Atualiza a altura deste nó ancestral
    node->altura = 1 + max(altura(node->esq), altura(node->dir));
    
    // 3. Obtém o fator de balanceamento
    int balance = getBalance(node);
    
    // 4. Se o nó ficou desbalanceado, há 4 casos:
    
    // Caso Esquerda-Esquerda
    if (balance > 1 && valor < node->esq->valor)
        return rotacaoDireita(node);
    
    // Caso Direita-Direita
    if (balance < -1 && valor > node->dir->valor)
        return rotacaoEsquerda(node);
    
    // Caso Esquerda-Direita
    if (balance > 1 && valor > node->esq->valor) {
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }
    
    // Caso Direita-Esquerda
    if (balance < -1 && valor < node->dir->valor) {
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }
    
    return node;
}

// Impressão da árvore "de lado"
void imprimir(Node* raiz, int nivel) {
    if (raiz == NULL) return;
    
    imprimir(raiz->dir, nivel + 1);
    
    for (int i = 0; i < nivel; i++)
        printf("    ");
    printf("%d(h=%d, b=%d)\n", raiz->valor, raiz->altura, getBalance(raiz));
    
    imprimir(raiz->esq, nivel + 1);
}

// Percurso em ordem
void emOrdem(Node* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

// Caso 1: Inserções que causam rotação simples à esquerda (RR)
void caso1() {
    printf("\n===== CASO 1: Rotação Simples à Esquerda (RR) =====\n");
    Node* raiz = NULL;
    
    printf("\nInserindo: 8, 4, 10, 9, 15, 12\n");
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 9);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 12);
    
    printf("\nÁrvore final:\n");
    imprimir(raiz, 0);
    printf("\nEm ordem: ");
    emOrdem(raiz);
    printf("\n");
}

// Caso 2: Inserções que causam rotação dupla (LR)
void caso2() {
    printf("\n===== CASO 2: Rotação Dupla Esquerda-Direita (LR) =====\n");
    Node* raiz = NULL;
    
    printf("\nInserindo: 8, 4, 10, 2, 6, 5\n");
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 5);
    
    printf("\nÁrvore final:\n");
    imprimir(raiz, 0);
    printf("\nEm ordem: ");
    emOrdem(raiz);
    printf("\n");
}

// Caso 3: Inserções que causam rotação simples à direita (LL)
void caso3() {
    printf("\n===== CASO 3: Rotação Simples à Direita (LL) =====\n");
    Node* raiz = NULL;
    
    printf("\nInserindo: 8, 10, 4, 6, 2, 3\n");
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 3);
    
    printf("\nÁrvore final:\n");
    imprimir(raiz, 0);
    printf("\nEm ordem: ");
    emOrdem(raiz);
    printf("\n");
}

// Caso 4: Inserções que causam rotação dupla (RL)
void caso4() {
    printf("\n===== CASO 4: Rotação Dupla Direita-Esquerda (RL) =====\n");
    Node* raiz = NULL;
    
    printf("\nInserindo: 8, 4, 12, 14, 10, 9\n");
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 14);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 9);
    
    printf("\nÁrvore final:\n");
    imprimir(raiz, 0);
    printf("\nEm ordem: ");
    emOrdem(raiz);
    printf("\n");
}

int main() {
    caso1();
    caso2();
    caso3();
    caso4();
    
    return 0;
}
