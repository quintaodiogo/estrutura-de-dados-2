/*Diogo de Paula Quintão(202207108) e João Pedro da Costa Reis(202206124)*/
#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    char* string;
    struct No* proximo;
} No;

typedef struct Lista {
    No* cabeca;
} Lista;

Lista* criar_lista();

int inserir_na_lista(Lista* lista, const char* valor);
void liberar_lista(Lista* lista);
void imprimir_lista(Lista* lista);

#endif 
