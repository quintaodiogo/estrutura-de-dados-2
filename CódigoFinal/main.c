#include <stdio.h>
#include <stdlib.h>
#include "arvore_b.h"

// =============================================================
// 1. FUNÇÕES AUXILIARES DE CONSTRUÇÃO MANUAL 
// =============================================================

// Função auxiliar para facilitar a construção manual dos nós para os testes
BTreeNode* criarNoManual(int n, int k1, int k2, int k3, int k4, bool folha) {
    BTreeNode* no = criarNo(folha);
    no->n = n;
    if (n >= 1) no->chaves[0] = k1;
    if (n >= 2) no->chaves[1] = k2;
    if (n >= 3) no->chaves[2] = k3;
    if (n >= 4) no->chaves[3] = k4;
    return no;
}

// Constrói a árvore base (Para testes G, H, J, C)
BTreeNode* construirArvoreBaseSlide39() {
    // 1. Criar as Folhas
    BTreeNode* f_abc = criarNoManual(3, 'A', 'B', 'C', 0, true);
    BTreeNode* f_fgh = criarNoManual(3, 'F', 'G', 'H', 0, true);
    BTreeNode* f_jk  = criarNoManual(2, 'J', 'K', 0, 0, true);
    BTreeNode* f_mn  = criarNoManual(2, 'M', 'N', 0, 0, true);
    BTreeNode* f_pq  = criarNoManual(2, 'P', 'Q', 0, 0, true);
    BTreeNode* f_uv  = criarNoManual(2, 'U', 'V', 0, 0, true);
    BTreeNode* f_yz  = criarNoManual(2, 'Y', 'Z', 0, 0, true);

    // 2. Criar Nós Internos (Nível 1)
    BTreeNode* ni_eil = criarNoManual(3, 'E', 'I', 'L', 0, false);
    ni_eil->filhos[0] = f_abc;
    ni_eil->filhos[1] = f_fgh;
    ni_eil->filhos[2] = f_jk;
    ni_eil->filhos[3] = f_mn;

    BTreeNode* ni_tw = criarNoManual(2, 'T', 'W', 0, 0, false);
    ni_tw->filhos[0] = f_pq;
    ni_tw->filhos[1] = f_uv;
    ni_tw->filhos[2] = f_yz;

    // 3. Criar Raiz: [O]
    BTreeNode* raiz = criarNoManual(1, 'O', 0, 0, 0, false);
    raiz->filhos[0] = ni_eil;
    raiz->filhos[1] = ni_tw;

    return raiz;
}

// Constrói a árvore específica para o teste (Remoção de K)
BTreeNode* construirArvoreSlide56() {
    // Folhas da Esquerda
    BTreeNode* f_ab = criarNoManual(2, 'A', 'B', 0, 0, true);
    BTreeNode* f_fi = criarNoManual(2, 'F', 'I', 0, 0, true);
    BTreeNode* f_mn = criarNoManual(2, 'M', 'N', 0, 0, true);

    // Folhas da Direita
    BTreeNode* f_pq = criarNoManual(2, 'P', 'Q', 0, 0, true);
    BTreeNode* f_uv = criarNoManual(2, 'U', 'V', 0, 0, true);
    BTreeNode* f_yz = criarNoManual(2, 'Y', 'Z', 0, 0, true);

    // Nó Interno Esquerdo [E, K]
    BTreeNode* ni_ek = criarNoManual(2, 'E', 'K', 0, 0, false);
    ni_ek->filhos[0] = f_ab;
    ni_ek->filhos[1] = f_fi;
    ni_ek->filhos[2] = f_mn;

    // Nó Interno Direito [T, W]
    BTreeNode* ni_tw = criarNoManual(2, 'T', 'W', 0, 0, false);
    ni_tw->filhos[0] = f_pq;
    ni_tw->filhos[1] = f_uv;
    ni_tw->filhos[2] = f_yz;

    // Raiz [O]
    BTreeNode* raiz = criarNoManual(1, 'O', 0, 0, 0, false);
    raiz->filhos[0] = ni_ek;
    raiz->filhos[1] = ni_tw;

    return raiz;
}

// Função local para limpar memória
void limparMemoriaTeste(BTreeNode* raiz) {
    if (raiz == NULL) return;
    if (!raiz->folha) {
        for (int i = 0; i <= raiz->n; i++) {
            limparMemoriaTeste(raiz->filhos[i]);
        }
    }
    free(raiz);
}

// =============================================================
// 2. FUNÇÕES DE TESTE (EXECUTORES)
// =============================================================

void executarTesteBusca() {
    printf("\n==================================================\n");
    printf("   EXECUTANDO TESTE 1: BUSCA EM ARVORE B\n");
    printf("==================================================\n");

    BTreeNode* raiz = criarNo(true);
    int valores[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    printf("1. Criando arvore e inserindo valores: { ");
    for(int i=0; i<n; i++) {
        printf("%d ", valores[i]);
        inserir(&raiz, valores[i]);
    }
    printf("}\n\n");

    printf("--- Estado da Arvore para a Busca ---\n");
    imprimirArvore(raiz, 0, false); 
    printf("-------------------------------------\n");

    int chaveExistente = 60;
    printf("\n[Teste A] Buscando chave %d ...\n", chaveExistente);
    BTreeNode* resultado = buscarChave(raiz, chaveExistente);
    
    if (resultado != NULL) {
        printf("RESULTADO: Encontrado! A chave %d foi encontrada.\n", chaveExistente);
    } else {
        printf("RESULTADO: ERRO! Deveria ter encontrado.\n");
    }

    int chaveInexistente = 99;
    printf("\n[Teste B] Buscando chave %d ...\n", chaveInexistente);
    resultado = buscarChave(raiz, chaveInexistente);

    if (resultado == NULL) {
        printf("RESULTADO: Não encontrado! A chave %d nao foi encontrada.\n", chaveInexistente);
    } else {
        printf("RESULTADO: ERRO! Achou algo que nao existe.\n");
    }

    limparMemoriaTeste(raiz);
    printf("\nTeste de Busca Finalizado.\n");
}

void executarTesteInsercao() {
    printf("\n==================================================\n");
    printf("   EXECUTANDO TESTE 2: INSERCAO \n");
    printf("==================================================\n");

    BTreeNode* raiz = criarNo(true);

    printf("\n[Passo 1] Construindo estado inicial \n");
    int valores_iniciais[] = {20, 40, 60, 80, 70, 10, 30, 15, 75, 85, 90, 25, 35, 50};
    int n = sizeof(valores_iniciais) / sizeof(valores_iniciais[0]);

    for (int i = 0; i < n; i++) {
        inserir(&raiz, valores_iniciais[i]);
    }

    printf(">>> ESTADO 1: Arvore Inicial (Antes de inserir 22 e 27) <<<\n");
    printf("Verifique: Raiz deve ter [20, 35, 60, 80]\n");
    imprimirArvore(raiz, 0, false); 
    printf("--------------------------------------------------\n");

    printf("\n[Passo 2] Inserindo 22 e 27...\n");
    inserir(&raiz, 22);
    inserir(&raiz, 27);

    printf(">>> ESTADO 2: Apos inserir 22 e 27  <<<\n");
    printf("Resultado: O filho que tinha [25, 30] agora encheu: [22, 25, 27, 30]\n");
    imprimirArvore(raiz, 0, false);
    printf("--------------------------------------------------\n");

    printf("\n[Passo 3] Inserindo 32... (Causa Split em Cascata)\n");
    inserir(&raiz, 32);

    printf(">>> ESTADO 3: Apos inserir 32  <<<\n");
    printf("Resultado: A raiz antiga explodiu. Nova raiz deve ser [35].\n");
    imprimirArvore(raiz, 0, false);
    printf("--------------------------------------------------\n");

    limparMemoriaTeste(raiz);
    printf("\nTeste de Insercao Finalizado.\n");
}

void executarTesteRemocao() {
    int subOpcao;
    BTreeNode* raiz = NULL;

    printf("\n==================================================\n");
    printf("   EXECUTANDO TESTE 3: REMOCAO \n");
    printf("==================================================\n");
    printf("Escolha o cenario:\n");
    printf("1. Sequencia G -> H -> J -> C \n");
    printf("2. Remocao do T \n");
    printf("3. Remocao do K \n");
    printf("Escolha: ");
    scanf("%d", &subOpcao);

    if (subOpcao == 1) {
        printf("\n--- CENARIO 1: Remocoes Sequenciais (G, H, J, C) ---\n");
        
        raiz = construirArvoreBaseSlide39();
        printf("\n>>> ESTADO INICIAL <<<\n");
        imprimirArvore(raiz, 0, true);
        printf("--------------------------------------------------\n");

        printf("\n[Passo 1] Removendo 'G'...\n");
        remover(&raiz, 'G');
        imprimirArvore(raiz, 0, true);
        printf("Verificacao: No [F,G,H] virou [F,H]. Sem underflow.\n");

        printf("\n[Passo 2] Removendo 'H'...\n");
        remover(&raiz, 'H');
        imprimirArvore(raiz, 0, true);
        printf("Verificacao: [F,H] virou [F] (Underflow). Empréstimo do irmao esquerdo.\n");

        printf("\n[Passo 3] Removendo 'J'...\n");
        remover(&raiz, 'J');
        imprimirArvore(raiz, 0, true);
        printf("Verificacao: [J,K] virou [K]. Merge com [E,F].\n");

        printf("\n[Passo 4] Removendo 'C'...\n");
        remover(&raiz, 'C');
        imprimirArvore(raiz, 0, true);
        printf("Verificacao: 'C' substituido. Arvore balanceada.\n");

        limparMemoriaTeste(raiz);
        printf("\nFim do Cenario 1.\n");
    }
    else if (subOpcao == 2) {
        printf("\n--- CENARIO 2: Remocao do T ---\n");
        
        // Para chegar no estado do Slide 126, precisamos da árvore base 
        // menos G e H. 
        raiz = construirArvoreBaseSlide39();
        remover(&raiz, 'G');
        remover(&raiz, 'H');
        
        printf("\n>>> ESTADO INICIAL (Pos remocao de G e H) <<<\n");
        imprimirArvore(raiz, 0, true);
        printf("--------------------------------------------------\n");

        printf("\n[Passo Unico] Removendo 'T'...\n");
        remover(&raiz, 'T');
        imprimirArvore(raiz, 0, true);
        printf("Verificacao: 'T' removido. Ocorreu combinação e empréstimo nos filhos da direita.\n");
        // Nota: O L sobe para a raiz e O descendo.
        // O filho [M,N] muda de pai.

        limparMemoriaTeste(raiz);
        printf("\nFim do Cenario 2.\n");
    }
    else if (subOpcao == 3) {
        printf("\n--- CENARIO 3: Remocao do K ---\n");
        
        // Este cenário usa uma árvore totalmente diferente das anteriores
        raiz = construirArvoreSlide56();
        
        printf("\n>>> ESTADO INICIAL <<<\n");
        imprimirArvore(raiz, 0, true);
        printf("--------------------------------------------------\n");

        printf("\n[Passo Unico] Removendo 'K'...\n");
        remover(&raiz, 'K');
        imprimirArvore(raiz, 0, true);
        printf("Verificacao: Fusao em cascata. Raiz possui agora [E, O, T, W].\n");

        limparMemoriaTeste(raiz);
        printf("\nFim do Cenario 3.\n");
    }
    else {
        printf("Opcao invalida.\n");
    }
}

// =============================================================
// MENU PRINCIPAL
// =============================================================
int main() {
    int opcao;

    do {
        printf("\n#############################################\n");
        printf("      PROJETO ARVORE B - APRESENTACAO\n");
        printf("#############################################\n");
        printf("1. Teste de Implementacao da BUSCA\n");
        printf("2. Teste de INSERCAO\n");
        printf("3. Teste de REMOCAO (Casos Diversos)\n");
        printf("0. Sair\n");
        printf("\nEscolha o teste para rodar: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                executarTesteBusca();
                break;
            case 2:
                executarTesteInsercao();
                break;
            case 3:
                executarTesteRemocao();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar(); getchar(); 
        }

    } while (opcao != 0);

    return 0;
}
