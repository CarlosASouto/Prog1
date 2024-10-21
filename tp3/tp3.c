/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

void imprimeVetor (struct racional **vet, int tam)
{
    printf ("VETOR = ");
    for (int i = 0; i < tam; i++)
    {
        imprime_r (vet[i]);
        if (i != tam - 1)
            printf (" ");
    }
    printf ("\n");
}

void removeInvalidos (struct racional **vet, int *tam)
{
    int i, j = 0;

    for (i = 0; i < *tam; i++)
        if (valido_r (vet[i]))
            vet[j++] = vet[i]; // Se valido, coloca o ponteiro na nova posicao
        else
        {
            destroi_r (vet[i]); // Se invalido libera a memoria
            vet[i] = NULL;
        }
    *tam = j; // Atualiza o tamanho do vetor
}

void trocaElementos (struct racional **vet, int a, int b)
{
    struct racional *temp = vet[a];
    vet[a] = vet[b];
    vet[b] = temp;
}

/*Ordena o vetor por Bubble Sort*/
void bubbleSort (struct racional **vet, int tam)
{
    if (tam < 1)
        return;

    for (int i = 0; i < tam - 1; i++)
        if (compara_r (vet[i], vet[i + 1]) == 1)
            trocaElementos (vet, i, i + 1);

    bubbleSort (vet, tam - 1);
}
/* programa principal */
int main ()
{
    int n = 0;
    long num, den;
    struct racional **vet;
    struct racional *soma = cria_r (0, 1);
    struct racional *aux = cria_r (0, 1);

    while (n <= 0 || n >= 100)
        scanf ("%d", &n);

    if (!(vet = malloc (sizeof (struct racional *) * n)))
    {
        fprintf (stderr, "Alocacao de memoria falhou\n");
        exit (1);
    }

    for (int i = 0; i < n; i++)
    {
        scanf ("%ld %ld", &num, &den);
        vet[i] = cria_r (num, den);
    }

    imprimeVetor (vet, n);

    removeInvalidos (vet, &n);

    imprimeVetor (vet, n);

    bubbleSort (vet, n);

    imprimeVetor (vet, n);

    for (int i = 0; i < n; i++)
    {
        soma_r (soma, vet[i], aux);
        *soma = *aux;
    }

    destroi_r (aux);
    aux = NULL;

    printf ("SOMA = ");
    imprime_r (soma);
    printf ("\n");

    for (int i = 0; i < n; i++)
    {
        destroi_r (vet[i]);
        vet[i] = NULL;
    }

    imprimeVetor (vet, n);

    free (vet);
    vet = NULL;

    destroi_r (soma);
    soma = NULL;

    return 0;
}
