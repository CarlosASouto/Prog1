// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples


#include <stdlib.h>
#include <stdio.h>
#include "fprio.h"

struct fprio_t *fprio_cria ()
{
    struct fprio_t *fila = (struct fprio_t *) malloc (sizeof(struct fprio_t));
    
    //Erro de alocação
    if (fila == NULL)
        return NULL;

    fila->prim = NULL;
    fila->num = 0;

    return fila;
}

struct fprio_t *fprio_destroi (struct fprio_t *f)
{
    if (f == NULL)
        return NULL;

    struct fpnodo_t *nodo_atual = f->prim;
    struct fpnodo_t *nodo_prox;

    //Percorre todos os nodos da fila liberando-os
    while (nodo_atual != NULL)
    {
        nodo_prox = nodo_atual->prox;
        free (nodo_atual->item);
        nodo_atual->item = NULL;
        
        free (nodo_atual);

        nodo_atual = nodo_prox;
    }

    free (f);
    f = NULL;
    
    return NULL;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
    if (f == NULL || item == NULL)
        return -1;

    //Verifica se o item já está na fila
    struct fpnodo_t *nodo_atual = f->prim;
    while (nodo_atual != NULL)
    {
        if (nodo_atual->item == item){
            return -1;
        }
        nodo_atual = nodo_atual->prox;
    }
    
    //Cria novo nodo
    struct fpnodo_t *novo_nodo = (struct fpnodo_t *) malloc (sizeof(struct fpnodo_t));
    if (novo_nodo == NULL) //Falha na alocação
        return -1;
    
    novo_nodo->item = item;
    novo_nodo->tipo = tipo;
    novo_nodo->prio = prio;
    novo_nodo->prox = NULL;

    //Fila vazia ou prioridade maior (insere no começo)
    if (f->prim == NULL || prio < f->prim->prio)
    {
        novo_nodo->prox = f->prim;
        f->prim = novo_nodo;
    }
    else //Encontra a posição correta
    {
        nodo_atual = f->prim;
        while (nodo_atual->prox != NULL && nodo_atual->prox->prio <= prio)
            nodo_atual = nodo_atual->prox;

        novo_nodo->prox = nodo_atual->prox;
        nodo_atual->prox = novo_nodo;
    }

    f->num++;

    return f->num;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
    if (f == NULL || f->prim == NULL)
        return NULL;

    if (tipo == NULL || prio == NULL)
        return NULL;
    
    struct fpnodo_t *nodo_remov = f->prim;

    *tipo = nodo_remov->tipo;
    *prio = nodo_remov->prio;

    void *item_remov = nodo_remov->item;

    f->prim = nodo_remov->prox;

    free (nodo_remov);
    nodo_remov = NULL;

    f->num--;

    return item_remov;
}

int fprio_tamanho (struct fprio_t *f)
{
    if (f == NULL)
        return -1;
    
    return f->num;
}

void fprio_imprime (struct fprio_t *f)
{
    if (f == NULL || f->prim == NULL)
        return;

    struct fpnodo_t *nodo_atual = f->prim;

    while (nodo_atual != NULL)
    {
        printf("(%d %d)", nodo_atual->tipo, nodo_atual->prio);

        nodo_atual = nodo_atual->prox;

        if (nodo_atual != NULL)
            printf (" ");

    }
}