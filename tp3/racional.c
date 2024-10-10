/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b)
{
  if (b==0)
     return a;

  return mdc (b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return ((a * b) / mdc (a, b));
}

int valido_r (struct racional *r)
{
   if (r->den == 0 || r == NULL)
     return 0;
   
   return 1;
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r (struct racional *r)
{
  if (!valido_r (r) || r == NULL)
     return 0;

  long divisor = mdc (r->num, r->den);
  r->num = r->num / divisor;
  r->den = r->den / divisor;
  if (r->den < 0){
     r->num = r->num * -1;
     r->den = r->den * -1;
  }

  return 1;
}

struct racional *cria_r (long numerador, long denominador)
{
  struct racional *r;

  if (!(r = malloc (sizeof (struct racional))))
  {
     fprintf (stderr, "Alocacao de memoria falhou \n");
     return NULL;
  }

  r->num = numerador;
  r->den = denominador;

  return r;
}

void destroi_r (struct racional *r)
{
  free (r);
  r = NULL;
}

void imprime_r (struct racional *r)
{
  simplifica_r (r);

  if (r == NULL){
     printf ("NULL ");
     return;
  }
  if (!valido_r (r)){
     printf ("NaN ");
     return;
  }
  if (r->num == 0 || r->den ==1){
     printf ("%ld ", r->num);
     return;
  }
  if (r->num == r->den){
     printf ("%d ", 1);
     return;
  }

  printf ("%ld/%ld ", r->num, r->den);
}

int compara_r (struct racional *r1, struct racional *r2)
{
  long den = mmc (r1->den, r2->den);
  long n1 = den / r1->den * r1->num;
  long n2 = den / r2->den * r2->num;

  if (!valido_r (r1) || !valido_r (r2) || r1 == NULL || r2 == NULL)
     return -2;
  if (n1 < n2)
     return -1;
  if (n1 == n2)
     return 0;

  return 1;
}

int soma_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r1 == NULL || r2 == NULL)
    return 0;
  r3->den = mmc (r1->den, r2->den);
  r3->num = (r3->den / r1->den * r1->num) + (r3->den / r2->den * r2->num);
  simplifica_r (r3);

  return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r1 == NULL || r2 == NULL)
    return 0;
  r3->den = mmc (r1->den, r2->den);
  r3->num = (r3->den / r1->den * r1->num) - (r3->den / r2->den * r2->num);
  simplifica_r (r3);

  return 1;
}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r1 == NULL || r2 == NULL)
    return 0;
  r3->den = r1->den * r2->den;
  r3->num = r1->num * r2->num;
  simplifica_r (r3);

  return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r1 == NULL || r2 == NULL)
    return 0;
  r3->den = r1->den * r2->num;
  r3->num = r1->num * r2->den;
  simplifica_r (r3);

  return 1;
}
/* implemente as demais funções de racional.h aqui */
