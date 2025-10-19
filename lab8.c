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

// Altura da árvore
int altura(Node* raiz) {
    if (raiz == NULL) return 0;
    int he = altura(raiz->esq);
    int hd = altura(raiz->dir);
    return (he > hd ? he : hd) + 1;
}

// Fator de balanceamento
int fatorBalanceamento(Node* raiz) {
    if (raiz == NULL) return 0;
    return altura(raiz->esq) - altura(raiz->dir);
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

// Inserção com balanceamento AVL 
Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) return novoNo(valor);
    
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    else
        return raiz;
    
    int fb = fatorBalanceamento(raiz);
    
    // Caso Esquerda-Esquerda
    if (fb > 1 && raiz->esq && valor < raiz->esq->valor)
        return rotacaoDireita(raiz);
    
    // Caso Direita-Direita
    if (fb < -1 && raiz->dir && valor > raiz->dir->valor)
        return rotacaoEsquerda(raiz);
    
    // Caso Esquerda-Direita
    if (fb > 1 && raiz->esq && valor > raiz->esq->valor) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    
    // Caso Direita-Esquerda
    if (fb < -1 && raiz->dir && valor < raiz->dir->valor) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    
    return raiz;
}

// Impressão da árvore
void imprimir(Node* raiz, int nivel) {
    if (raiz == NULL) return;
    imprimir(raiz->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d(h=%d, fb=%d)\n", raiz->valor, altura(raiz), fatorBalanceamento(raiz));
    imprimir(raiz->esq, nivel + 1);
}

// Caso 1 - Rotação simples à esquerda (Direita-Direita)
void caso1() {
    printf("\n===== CASO 1: Rotação simples à esquerda =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4);
    raiz->dir = novoNo(10);
    raiz->dir->esq = novoNo(9);
    raiz->dir->dir = novoNo(15);
    raiz->dir->dir->dir = novoNo(20); 
    printf("\nÁrvore antes da rotação:\n");
    imprimir(raiz, 0);

    raiz = rotacaoEsquerda(raiz);

    printf("\nÁrvore após rotação à esquerda:\n");
    imprimir(raiz, 0);
}

// Caso 2 - Rotação dupla Esquerda-Direita
void caso2() {
    printf("\n===== CASO 2: Rotação dupla (Esq-Dir) =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4);
    raiz->dir = novoNo(10);
    raiz->esq->esq = novoNo(2);
    raiz->esq->dir = novoNo(6);
    raiz->esq->dir->esq = novoNo(5);

    printf("\nÁrvore antes das rotações:\n");
    imprimir(raiz, 0);

    raiz->esq = rotacaoEsquerda(raiz->esq);
    raiz = rotacaoDireita(raiz);

    printf("\nÁrvore após as rotações:\n");
    imprimir(raiz, 0);
}

// Caso 3 - Rotação simples à direita (Esquerda-Esquerda) - CORRIGIDO
void caso3() {
    printf("\n===== CASO 3: Rotação simples à direita =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4);
    raiz->dir = novoNo(10);
    raiz->esq->esq = novoNo(2);
    raiz->esq->dir = novoNo(6);
    raiz->esq->esq->esq = novoNo(1); 
    printf("\nÁrvore antes da rotação:\n");
    imprimir(raiz, 0);

    raiz = rotacaoDireita(raiz);

    printf("\nÁrvore após rotação à direita:\n");
    imprimir(raiz, 0);
}

// Caso 4 - Rotação dupla Direita-Esquerda - CORRIGIDO
void caso4() {
    printf("\n===== CASO 4: Rotação dupla (Dir-Esq) =====\n");
    Node* raiz = novoNo(8);
    raiz->esq = novoNo(4); 
    raiz->dir = novoNo(12); 
    raiz->dir->esq = novoNo(10);
    raiz->dir->dir = novoNo(14);
    raiz->dir->esq->esq = novoNo(9); 

    printf("\nÁrvore antes das rotações:\n");
    imprimir(raiz, 0);

    raiz->dir = rotacaoDireita(raiz->dir);
    raiz = rotacaoEsquerda(raiz);

    printf("\nÁrvore após as rotações:\n");
    imprimir(raiz, 0);
}

// Função para liberar memória
void destruir(Node* raiz) {
    if (raiz == NULL) return;
    destruir(raiz->esq);
    destruir(raiz->dir);
    free(raiz);
}

// Demonstração de inserção com balanceamento automático
void casoInsercaoAVL() {
    printf("\n===== DEMONSTRAÇÃO: Inserção com balanceamento AVL =====\n");
    Node* raiz = NULL;
    int valores[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < n; i++) {
        printf("\nInserindo %d:\n", valores[i]);
        raiz = inserir(raiz, valores[i]);
        imprimir(raiz, 0);
    }
    
    destruir(raiz);
}

int main() {
    caso1();
    caso2();
    caso3();
    caso4();
    casoInsercaoAVL();
    return 0;
}
