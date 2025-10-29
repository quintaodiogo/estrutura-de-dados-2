/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
//Implementação das principais operações de Árvores B
//1 - Use uma árvore B com ordem 5 (4 Chaves e 5 Filhos)
//2 - Implemente a Busca
//3 - Implemente a Inserção de Chaves (tratar todos os casos possíveis de divisão)
//4 - Implemente a Remoção de Chaves (tratar todos os casos possíveis, exceto a redistribuição)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDEM 5
#define MAX_CHAVES (ORDEM - 1)  // 4 chaves
#define MIN_CHAVES (ORDEM / 2 - 1)  // 2 chaves (mínimo para nós internos)

// Estrutura do nó da Árvore B
typedef struct BTreeNode {
    int chaves[MAX_CHAVES];           // Array de chaves
    struct BTreeNode *filhos[ORDEM];   // Array de ponteiros para filhos
    int num_chaves;                    // Número atual de chaves
    bool eh_folha;                     // Verdadeiro se o nó é folha
} BTreeNode;

// Estrutura da Árvore B
typedef struct BTree {
    BTreeNode *raiz;
} BTree;

// Cria um novo nó
BTreeNode* criar_no(bool eh_folha) {
    BTreeNode *novo = (BTreeNode*)malloc(sizeof(BTreeNode));
    novo->num_chaves = 0;
    novo->eh_folha = eh_folha;
    
    for (int i = 0; i < ORDEM; i++) {
        novo->filhos[i] = NULL;
    }
    
    return novo;
}

// Cria uma nova árvore B
BTree* criar_arvore() {
    BTree *arvore = (BTree*)malloc(sizeof(BTree));
    arvore->raiz = criar_no(true);
    return arvore;
}

// Busca uma chave em um nó
int buscar_chave_no_no(BTreeNode *no, int chave) {
    int i = 0;
    while (i < no->num_chaves && chave > no->chaves[i]) {
        i++;
    }
    return i;
}

BTreeNode* buscar_recursivo(BTreeNode *no, int chave) {
    if (no == NULL) return NULL;
    
    int i = buscar_chave_no_no(no, chave);
    
    // Chave encontrada
    if (i < no->num_chaves && no->chaves[i] == chave) {
        return no;
    }
    
    // Se é folha e não encontrou, a chave não existe
    if (no->eh_folha) {
        return NULL;
    }
    
    // Buscar no filho apropriado
    return buscar_recursivo(no->filhos[i], chave);
}

bool buscar(BTree *arvore, int chave) {
    BTreeNode *resultado = buscar_recursivo(arvore->raiz, chave);
    return resultado != NULL;
}

void dividir_filho(BTreeNode *pai, int indice) {
    BTreeNode *cheio = pai->filhos[indice];
    BTreeNode *novo = criar_no(cheio->eh_folha);
    
    int meio = MAX_CHAVES / 2;  // índice 2 (terceira chave)
    novo->num_chaves = MAX_CHAVES - meio - 1;  // 1 chave
    
    // Copiar as chaves maiores para o novo nó
    for (int i = 0; i < novo->num_chaves; i++) {
        novo->chaves[i] = cheio->chaves[i + meio + 1];
    }
    
    // Se não é folha, copiar os filhos também
    if (!cheio->eh_folha) {
        for (int i = 0; i <= novo->num_chaves; i++) {
            novo->filhos[i] = cheio->filhos[i + meio + 1];
        }
    }
    
    cheio->num_chaves = meio;
    
    // Inserir a chave do meio no pai
    for (int i = pai->num_chaves; i > indice; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }
    pai->filhos[indice + 1] = novo;
    
    for (int i = pai->num_chaves - 1; i >= indice; i--) {
        pai->chaves[i + 1] = pai->chaves[i];
    }
    pai->chaves[indice] = cheio->chaves[meio];
    pai->num_chaves++;
}

void inserir_nao_cheio(BTreeNode *no, int chave) {
    int i = no->num_chaves - 1;
    
    if (no->eh_folha) {
        // Inserir a chave na posição correta
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->num_chaves++;
    } else {
        // Encontrar o filho onde a chave deve ser inserida
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;
        
        // Verificar se o filho está cheio
        if (no->filhos[i]->num_chaves == MAX_CHAVES) {
            dividir_filho(no, i);
            
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        inserir_nao_cheio(no->filhos[i], chave);
    }
}

void inserir(BTree *arvore, int chave) {
    BTreeNode *raiz = arvore->raiz;
    
    // Se a raiz está cheia, criar nova raiz
    if (raiz->num_chaves == MAX_CHAVES) {
        BTreeNode *nova_raiz = criar_no(false);
        nova_raiz->filhos[0] = raiz;
        dividir_filho(nova_raiz, 0);
        arvore->raiz = nova_raiz;
        inserir_nao_cheio(nova_raiz, chave);
    } else {
        inserir_nao_cheio(raiz, chave);
    }
}

// Pegar a chave predecessora (maior chave da subárvore esquerda)
int pegar_predecessor(BTreeNode *no, int indice) {
    BTreeNode *atual = no->filhos[indice];
    while (!atual->eh_folha) {
        atual = atual->filhos[atual->num_chaves];
    }
    return atual->chaves[atual->num_chaves - 1];
}

// Pegar a chave sucessora (menor chave da subárvore direita)
int pegar_sucessor(BTreeNode *no, int indice) {
    BTreeNode *atual = no->filhos[indice + 1];
    while (!atual->eh_folha) {
        atual = atual->filhos[0];
    }
    return atual->chaves[0];
}

// Mesclar filho com irmão (SEM redistribuição)
void mesclar(BTreeNode *no, int indice) {
    BTreeNode *filho = no->filhos[indice];
    BTreeNode *irmao = no->filhos[indice + 1];
    
    // Puxar a chave do pai e mesclar com o irmão direito
    filho->chaves[filho->num_chaves] = no->chaves[indice];
    
    // Copiar as chaves do irmão para o filho
    for (int i = 0; i < irmao->num_chaves; i++) {
        filho->chaves[filho->num_chaves + 1 + i] = irmao->chaves[i];
    }
    
    // Copiar os ponteiros dos filhos do irmão
    if (!filho->eh_folha) {
        for (int i = 0; i <= irmao->num_chaves; i++) {
            filho->filhos[filho->num_chaves + 1 + i] = irmao->filhos[i];
        }
    }
    
    // Atualizar o número de chaves
    filho->num_chaves += irmao->num_chaves + 1;
    
    // Mover as chaves do pai uma posição para trás
    for (int i = indice + 1; i < no->num_chaves; i++) {
        no->chaves[i - 1] = no->chaves[i];
    }
    
    // Mover os ponteiros dos filhos uma posição para trás
    for (int i = indice + 2; i <= no->num_chaves; i++) {
        no->filhos[i - 1] = no->filhos[i];
    }
    
    no->num_chaves--;
    
    // Liberar memória do irmão
    free(irmao);
}

void remover_do_no(BTreeNode *no, int chave) {
    int indice = buscar_chave_no_no(no, chave);
    
    if (indice < no->num_chaves && no->chaves[indice] == chave) {
        // CASO 1: A chave está neste nó
        if (no->eh_folha) {
            // Caso 1a: Nó é folha - simplesmente remover
            for (int i = indice + 1; i < no->num_chaves; i++) {
                no->chaves[i - 1] = no->chaves[i];
            }
            no->num_chaves--;
        } else {
            // Caso 2: Nó interno - substituir por predecessor ou sucessor
            if (no->filhos[indice]->num_chaves > MIN_CHAVES) {
                // Caso 2a: Filho esquerdo tem chaves suficientes
                int pred = pegar_predecessor(no, indice);
                no->chaves[indice] = pred;
                remover_do_no(no->filhos[indice], pred);
            } else if (no->filhos[indice + 1]->num_chaves > MIN_CHAVES) {
                // Caso 2b: Filho direito tem chaves suficientes
                int suc = pegar_sucessor(no, indice);
                no->chaves[indice] = suc;
                remover_do_no(no->filhos[indice + 1], suc);
            } else {
                // Caso 2c: Ambos têm o mínimo - mesclar e remover
                mesclar(no, indice);
                remover_do_no(no->filhos[indice], chave);
            }
        }
    } else {
        // CASO 3: A chave não está neste nó
        if (no->eh_folha) {
            printf("Chave %d não encontrada na árvore!\n", chave);
            return;
        }
        
        // Verificar se estamos no último filho
        bool flag = (indice == no->num_chaves);
        
        // Se o filho tem apenas o mínimo de chaves, mesclar antes de descer
        if (no->filhos[indice]->num_chaves <= MIN_CHAVES) {
            if (indice != no->num_chaves) {
                // Mesclar com o irmão direito
                mesclar(no, indice);
            } else {
                // Mesclar com o irmão esquerdo
                mesclar(no, indice - 1);
            }
        }
        
        // Recursão no filho apropriado após possível mesclagem
        if (flag && indice > no->num_chaves) {
            remover_do_no(no->filhos[indice - 1], chave);
        } else {
            remover_do_no(no->filhos[indice], chave);
        }
    }
}

void remover(BTree *arvore, int chave) {
    if (arvore->raiz == NULL) {
        printf("Árvore vazia!\n");
        return;
    }
    
    remover_do_no(arvore->raiz, chave);
    
    // Se a raiz ficou vazia, ajustar
    if (arvore->raiz->num_chaves == 0) {
        BTreeNode *tmp = arvore->raiz;
        if (arvore->raiz->eh_folha) {
            arvore->raiz = NULL;
        } else {
            arvore->raiz = arvore->raiz->filhos[0];
        }
        free(tmp);
    }
}

void imprimir_arvore_recursivo(BTreeNode *no, int nivel) {
    if (no == NULL) return;
    
    printf("Nível %d: [", nivel);
    for (int i = 0; i < no->num_chaves; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->num_chaves - 1) printf(", ");
    }
    printf("]\n");
    
    if (!no->eh_folha) {
        for (int i = 0; i <= no->num_chaves; i++) {
            imprimir_arvore_recursivo(no->filhos[i], nivel + 1);
        }
    }
}

void imprimir_arvore(BTree *arvore) {
    printf("\n=== Estrutura da Árvore B ===\n");
    if (arvore->raiz == NULL) {
        printf("Árvore vazia!\n");
    } else {
        imprimir_arvore_recursivo(arvore->raiz, 0);
    }
    printf("============================\n\n");
}

int main() {
    BTree *arvore = criar_arvore();
    int opcao, valor;
    
    printf("======================================\n");
    printf("   ÁRVORE B DE ORDEM 5\n");
    printf("   (4 chaves e 5 filhos por nó)\n");
    printf("======================================\n");
    printf("Implementação completa com:\n");
    printf("✓ Busca\n");
    printf("✓ Inserção (todos os casos de divisão)\n");
    printf("✓ Remoção (mesclagem, sem redistribuição)\n");
    printf("======================================\n\n");
    
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Inserir chave\n");
        printf("2. Remover chave\n");
        printf("3. Buscar chave\n");
        printf("4. Imprimir árvore\n");
        printf("5. Teste automático\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("\nDigite o valor a inserir: ");
                scanf("%d", &valor);
                inserir(arvore, valor);
                printf("✓ Valor %d inserido com sucesso!\n", valor);
                imprimir_arvore(arvore);
                break;
                
            case 2:
                printf("\nDigite o valor a remover: ");
                scanf("%d", &valor);
                remover(arvore, valor);
                imprimir_arvore(arvore);
                break;
                
            case 3:
                printf("\nDigite o valor a buscar: ");
                scanf("%d", &valor);
                if (buscar(arvore, valor)) {
                    printf("✓ Valor %d ENCONTRADO na árvore!\n", valor);
                } else {
                    printf("✗ Valor %d NÃO encontrado na árvore.\n", valor);
                }
                break;
                
            case 4:
                imprimir_arvore(arvore);
                break;
                
            case 5:
                printf("\n========== TESTE AUTOMÁTICO ==========\n");
                printf("Inserindo valores: 10, 20, 30, 40, 50, 60, 70, 80, 90, 100\n\n");
                
                int valores[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
                for (int i = 0; i < 10; i++) {
                    printf("Inserindo %d...\n", valores[i]);
                    inserir(arvore, valores[i]);
                }
                
                printf("\nÁrvore após inserções:\n");
                imprimir_arvore(arvore);
                
                printf("\nBuscando valor 50...\n");
                if (buscar(arvore, 50)) {
                    printf("✓ Valor 50 encontrado!\n");
                }
                
                printf("\nBuscando valor 999...\n");
                if (!buscar(arvore, 999)) {
                    printf("✗ Valor 999 não encontrado (correto).\n");
                }
                
                printf("\nRemovendo valor 50...\n");
                remover(arvore, 50);
                imprimir_arvore(arvore);
                
                printf("======================================\n");
                break;
                
            case 0:
                printf("\n✓ Encerrando programa...\n");
                break;
                
            default:
                printf("\n✗ Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
    
    return 0;
}
