/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

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
  struct racional temp = *a;

  *a = *b;
  *b = temp;
}

/* Ordena o vetor por bubblesort */
void bubbleSort (struct racional v[], int n)
{
  if (n < 1)
     return;
  
  for (int i = 0; i < n-1; i++)
     if (compara_r (v[i], v[i + 1]) == 1)
       trocaElementos (&v[i], &v[i + 1]);

  bubbleSort (v, n-1);
}
/* Imprime um vetor de racionais */
void imprimeVetor (struct racional v[], int tam) 
{
  printf ("VETOR = ");
  for (int i = 0; i < tam; i++)
     imprime_r (v[i]);
  printf ("\n");
}

/* Retorna o valor da soma de um vetor de racionais */
struct racional somaVetor (struct racional v[], int tam) 
{  
  struct racional soma = cria_r (0, 1);

  for (int i = 0; i < tam; i++)
     soma_r (soma, v[i], &soma);

  return soma;
}

/* programa principal */
int main ()
{
  struct racional v [100];
  struct racional soma;
  int n = 0;
  int num, den, i;

  while (n <= 0 || n >= 100)
     scanf ("%d", &n);
  for (i = 0; i < n; i++)
  {
     scanf ("%d %d", &num, &den);
     v[i] = cria_r (num, den);
  }

  imprimeVetor (v, n);

  removeInvalidos (v, &n);

  imprimeVetor (v, n);

  bubbleSort (v, n);

  imprimeVetor (v, n);

  soma = somaVetor (v, n);

  printf ("SOMA = ");
  imprime_r (soma);
  printf ("\n");

  return 0;
}
