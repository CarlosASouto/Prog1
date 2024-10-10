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
    imprime_r (vet[i]);
  printf ("\n");
}

/* Este algoritmo remove elementos invalidos do vetor substituindo-os
pelo proximo elemento e diminuindo o tamanho do vetor */
void removeInvalidos (struct racional v[], int *tam)
{
  int i, j;

  for (i = 0; i < *tam; i++)
     if (!valido_r (v[i])){
       for (j = i; j < *tam; j++)
          v[j] = v[j + 1]; // Este for substitui o valor do invalido pelo proximo elemento e ajusta o vetor para poder diminuir o tamanho
       (*tam)--;
       i--; //Decrementa o i para verificar a mesma posicao novamente
     }
}

void trocaElementos (struct racional *a, struct racional *b)
{
  struct racional *temp = a;
  a = b;
  b = temp;
}

void bubbleSort (struct racional **vet, int tam)
{
  if (tam < 1)
     return;
  
  for (int i = 0; i < tam-1; i++)
     if (compara_r (vet[i], vet[i + 1]) == 1)
       trocaElementos (vet[i], vet[i + 1]);
  
  bubbleSort (vet, tam-1);
}
/* programa principal */
int main ()
{
  int n = 0;
  long num, den;
  struct racional **vet;

  while (n <= 0 || n >= 100)
     scanf ("%d", &n);
  
  if (!(vet = malloc (sizeof(struct racional *) * n)))
  {
     fprintf (stderr, "Alocacao de memoria falhou\n");
     exit(1);
  }

  for (int i = 0; i < n; i++)
  {
    scanf ("%ld %ld", &num, &den);
    vet[i] = cria_r (num, den);
  }

  imprimeVetor (vet, n);

  bubbleSort (vet, n);

  imprimeVetor (vet, n);
  
}

