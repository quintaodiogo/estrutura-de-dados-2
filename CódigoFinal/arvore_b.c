/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/

#include <stdio.h>
#include <stdlib.h>
#include "arvore_b.h"

// ==========================================================
// FUNÇÕES AUXILIARES E DE IMPRESSÃO
// ==========================================================

BTreeNode* criarNo(bool folha) {
    BTreeNode* novo = (BTreeNode*)malloc(sizeof(BTreeNode));
    novo->folha = folha;
    novo->n = 0;
    for (int i = 0; i < M; i++) {
        novo->filhos[i] = NULL;
    }
    return novo;
}

static void imprimirChave(int k, bool usar_letras) {
    if (usar_letras && k >= 65 && k <= 90) {
        printf("'%c' ", (char)k);
    } else {
        printf("%d ", k);
    }
}

void imprimirArvore(BTreeNode* raiz, int nivel, bool usar_letras) {
    if (raiz == NULL) {
        printf("Arvore Vazia\n");
        return;
    }
    printf("Nivel %d: [ ", nivel);
    for (int i = 0; i < raiz->n; i++) {
        imprimirChave(raiz->chaves[i], usar_letras);
        if (i < raiz->n - 1) printf("| ");
    }
    printf("]\n");

    if (!raiz->folha) {
        for (int i = 0; i <= raiz->n; i++) {
            if (raiz->filhos[i] != NULL) {
                for(int j=0; j<=nivel; j++) printf("   ");
                printf("Filho %d -> ", i);
                imprimirArvore(raiz->filhos[i], nivel + 1, usar_letras);
            }
        }
    }
}

// ==========================================================
// OPERAÇÃO DE BUSCA
// ==========================================================

BTreeNode* buscarChave(BTreeNode* raiz, int k) {
    if (raiz == NULL) return NULL;
    int i = 0;
    while (i < raiz->n && k > raiz->chaves[i]) {
        i++;
    }
    if (i < raiz->n && k == raiz->chaves[i]) {
        return raiz;
    }
    if (raiz->folha) return NULL;
    return buscarChave(raiz->filhos[i], k);
}

// ==========================================================
// OPERAÇÃO DE INSERÇÃO
// ==========================================================

static bool inserirAux(BTreeNode* no, int k, int *chave_promovida, BTreeNode** filho_direito_promovido) {
    int pos;
    // Verifica se a chave já existe para evitar duplicatas
    for(pos = 0; pos < no->n; pos++){
        if(no->chaves[pos] == k) return false;
    }

    if (!no->folha) {
        pos = 0;
        while (pos < no->n && k > no->chaves[pos]) {
            pos++;
        }
        
        bool filho_dividiu = inserirAux(no->filhos[pos], k, chave_promovida, filho_direito_promovido);
        if (!filho_dividiu) return false;
        
        // Se o filho dividiu, a chave promovida deve ser inserida neste nó
        k = *chave_promovida;
    }

    // Lógica de inserção no nó atual (ou da chave k ou da promovida)
    if (no->n < M - 1) {
        int i = no->n;
        while (i > 0 && k < no->chaves[i-1]) {
            no->chaves[i] = no->chaves[i-1];
            no->filhos[i+1] = no->filhos[i];
            i--;
        }
        no->chaves[i] = k;
        if (!no->folha) {
            no->filhos[i+1] = *filho_direito_promovido;
        }
        no->n++;
        return false;
    } else {
        // Split (Divisão)
        int temp_chaves[M];
        BTreeNode* temp_filhos[M + 1];
        int i;

        // Copia dados atuais para temporários
        for (i = 0; i < M - 1; i++) {
            temp_chaves[i] = no->chaves[i];
            temp_filhos[i] = no->filhos[i];
        }
        temp_filhos[M - 1] = no->filhos[M - 1];

        // Insere ordenado no temporário
        i = M - 2;
        while (i >= 0 && k < temp_chaves[i]) {
            temp_chaves[i+1] = temp_chaves[i];
            temp_filhos[i+2] = temp_filhos[i+1];
            i--;
        }
        temp_chaves[i+1] = k;
        if (!no->folha) {
            temp_filhos[i+2] = *filho_direito_promovido;
        }

        // Divide
        int meio = M / 2;
        no->n = meio;
        for (i = 0; i < no->n; i++) {
            no->chaves[i] = temp_chaves[i];
            no->filhos[i] = temp_filhos[i];
        }
        no->filhos[no->n] = temp_filhos[no->n];

        BTreeNode* novo_dir = criarNo(no->folha);
        novo_dir->n = (M) - 1 - meio;
        for (i = 0; i < novo_dir->n; i++) {
            novo_dir->chaves[i] = temp_chaves[i + meio + 1];
            novo_dir->filhos[i] = temp_filhos[i + meio + 1];
        }
        novo_dir->filhos[novo_dir->n] = temp_filhos[M];

        *chave_promovida = temp_chaves[meio];
        *filho_direito_promovido = novo_dir;
        return true;
    }
}

void inserir(BTreeNode** raiz, int k) {
    int chave_promovida;
    BTreeNode* filho_direito_promovido;

    if (inserirAux(*raiz, k, &chave_promovida, &filho_direito_promovido)) {
        BTreeNode* nova_raiz = criarNo(false);
        nova_raiz->n = 1;
        nova_raiz->chaves[0] = chave_promovida;
        nova_raiz->filhos[0] = *raiz;
        nova_raiz->filhos[1] = filho_direito_promovido;
        *raiz = nova_raiz;
    }
}

// ==========================================================
// FUNÇÕES AUXILIARES DE REMOÇÃO (PRIVADAS)
// ==========================================================

static void removerDaFolha(BTreeNode *no, int idx) {
    for (int i = idx + 1; i < no->n; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }
    no->n--;
}

static int obterPredecessor(BTreeNode *no, int idx) {
    BTreeNode *atual = no->filhos[idx];
    while (!atual->folha) {
        atual = atual->filhos[atual->n];
    }
    return atual->chaves[atual->n - 1];
}

static int obterSucessor(BTreeNode *no, int idx) {
    BTreeNode *atual = no->filhos[idx + 1];
    while (!atual->folha) {
        atual = atual->filhos[0];
    }
    return atual->chaves[0];
}

static void merge(BTreeNode *no, int idx) {
    BTreeNode *filho = no->filhos[idx];
    BTreeNode *irmao = no->filhos[idx + 1];

    // Desce chave do pai
    filho->chaves[filho->n] = no->chaves[idx];

    // Copia chaves do irmão
    for (int i = 0; i < irmao->n; ++i) {
        filho->chaves[i + filho->n + 1] = irmao->chaves[i];
    }

    // Copia filhos do irmão
    if (!filho->folha) {
        for (int i = 0; i <= irmao->n; ++i) {
            filho->filhos[i + filho->n + 1] = irmao->filhos[i];
        }
    }

    filho->n += irmao->n + 1;

    // Remove chave do pai e ajusta filhos
    for (int i = idx + 1; i < no->n; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }
    for (int i = idx + 2; i <= no->n; ++i) {
        no->filhos[i - 1] = no->filhos[i];
    }
    no->n--;
    free(irmao);
}

static void emprestarDoAnterior(BTreeNode *no, int idx) {
    BTreeNode *filho = no->filhos[idx];
    BTreeNode *irmao = no->filhos[idx - 1];

    // Abre espaço no filho
    for (int i = filho->n - 1; i >= 0; --i) {
        filho->chaves[i + 1] = filho->chaves[i];
    }
    if (!filho->folha) {
        for (int i = filho->n; i >= 0; --i) {
            filho->filhos[i + 1] = filho->filhos[i];
        }
    }

    // Rotação: Pai desce, Irmão sobe
    filho->chaves[0] = no->chaves[idx - 1];
    if (!filho->folha) {
        filho->filhos[0] = irmao->filhos[irmao->n];
    }
    no->chaves[idx - 1] = irmao->chaves[irmao->n - 1];

    filho->n += 1;
    irmao->n -= 1;
}

static void emprestarDoProximo(BTreeNode *no, int idx) {
    BTreeNode *filho = no->filhos[idx];
    BTreeNode *irmao = no->filhos[idx + 1];

    // Rotação: Pai desce, Irmão sobe
    filho->chaves[filho->n] = no->chaves[idx];
    if (!filho->folha) {
        filho->filhos[(filho->n) + 1] = irmao->filhos[0];
    }
    no->chaves[idx] = irmao->chaves[0];

    // Ajusta irmão
    for (int i = 1; i < irmao->n; ++i) {
        irmao->chaves[i - 1] = irmao->chaves[i];
    }
    if (!irmao->folha) {
        for (int i = 1; i <= irmao->n; ++i) {
            irmao->filhos[i - 1] = irmao->filhos[i];
        }
    }

    filho->n += 1;
    irmao->n -= 1;
}

// Correção especial para o caso de Overflow na raiz causado por Merge em remoção
static void tratarEstouroRaiz(BTreeNode **raiz) {
    if ((*raiz)->n == M) {
        BTreeNode *antigaRaiz = *raiz;
        BTreeNode *novaRaiz = criarNo(false);
        novaRaiz->folha = false;
        BTreeNode *novoDir = criarNo(antigaRaiz->folha);
        
        int meio = 2; // (M=5)/2 = 2

        novaRaiz->chaves[0] = antigaRaiz->chaves[meio];
        novaRaiz->n = 1;

        novoDir->n = 2;
        novoDir->chaves[0] = antigaRaiz->chaves[3];
        novoDir->chaves[1] = antigaRaiz->chaves[4];

        if (!antigaRaiz->folha) {
            novoDir->filhos[0] = antigaRaiz->filhos[3];
            novoDir->filhos[1] = antigaRaiz->filhos[4];
            novoDir->filhos[2] = antigaRaiz->filhos[5];
        }

        antigaRaiz->n = 2; 

        novaRaiz->filhos[0] = antigaRaiz;
        novaRaiz->filhos[1] = novoDir;

        *raiz = novaRaiz;
    }
}

// ==========================================================
// OPERAÇÃO DE REMOÇÃO (PRINCIPAL)
// ==========================================================

static void removerChave(BTreeNode *no, int k) {
    int idx = 0;
    while (idx < no->n && no->chaves[idx] < k) {
        idx++;
    }

    if (idx < no->n && no->chaves[idx] == k) {
        if (no->folha) {
            removerDaFolha(no, idx);
        } else {
            BTreeNode *filhoEsq = no->filhos[idx];
            BTreeNode *filhoDir = no->filhos[idx + 1];

            if (filhoEsq->n >= 3) {
                int pred = obterPredecessor(no, idx);
                no->chaves[idx] = pred;
                removerChave(filhoEsq, pred);
            } else if (filhoDir->n >= 3) {
                int suc = obterSucessor(no, idx);
                no->chaves[idx] = suc;
                removerChave(filhoDir, suc);
            } else {
                merge(no, idx);
                removerChave(no->filhos[idx], k);
            }
        }
    } else {
        if (no->folha) {
            printf("A chave %d nao existe na arvore.\n", k);
            return;
        }

        bool flagUltimoFilho = (idx == no->n);
        BTreeNode *filho = no->filhos[idx];

        removerChave(filho, k); // Chamada Recursiva

        // Verifica e conserta na volta (Bottom-Up)
        if (filho->n < 2) {
            if (idx != 0 && no->filhos[idx - 1]->n >= 3) {
                emprestarDoAnterior(no, idx);
            } else if (idx != no->n && no->filhos[idx + 1]->n >= 3) {
                emprestarDoProximo(no, idx);
            } else {
                if (idx != 0) {
                    merge(no, idx - 1);
                } else {
                    merge(no, idx);
                }
            }
        }
    }
}

void remover(BTreeNode **raiz, int k) {
    if (*raiz == NULL) {
        printf("A arvore esta vazia.\n");
        return;
    }

    removerChave(*raiz, k);

    if ((*raiz)->n == 0) {
        BTreeNode *tmp = *raiz;
        if ((*raiz)->folha) {
            *raiz = NULL;
        } else {
            *raiz = (*raiz)->filhos[0];
        }
        free(tmp);
    } else if ((*raiz)->n >= M) {
        tratarEstouroRaiz(raiz);
    }
}

