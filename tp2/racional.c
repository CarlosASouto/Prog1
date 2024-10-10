/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  return ((rand() % (max - min + 1)) + min);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
  if (b==0)
     return a;

  return mdc (b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return ((a * b) / mdc (a, b));
}

int valido_r (struct racional r)
{
  if (r.den == 0)
     return 0;

  return 1;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
  if (!valido_r (r))
     return r;

  long divisor = mdc (r.num, r.den);
  r.num = r.num / divisor;
  r.den = r.den / divisor;
  if (r.den < 0){
     r.num = r.num * -1;
     r.den = r.den * -1;
  }

  return r;
}

struct racional cria_r (long numerador, long denominador)
{
  struct racional r;

  r.num = numerador;
  r.den = denominador;

  return simplifica_r(r);
}

struct racional sorteia_r (long min, long max)
{
  struct racional r;

  r.num = aleat (min, max);
  r.den = aleat (min, max);

  return simplifica_r(r);
}

void imprime_r (struct racional r)
{
  r = simplifica_r (r);

  if (!valido_r (r)){
     printf ("NaN ");
     return;
  }  
  if (r.num == 0 || r.den == 1){   
     printf ("%ld ", r.num);
     return;
  }
  if (r.num == r.den){
     printf ("%d ", 1);
     return;
  }

  printf ("%ld/%ld ", r.num, r.den);
}

int compara_r (struct racional r1, struct racional r2)
{
  if (!valido_r (r1) || !valido_r (r2))
     return -2;
  r1.num = r1.num * r2.den;
  r2.num = r2.num * r1.den;
  if (r1.num < r2.num)
     return -1;
  if (r1.num == r2.num)
     return 0;

  return 1;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2)){
     r3->den = 0;
     return 0;
  }
  r3->den = mmc (r1.den, r2.den);
  r3->num = (r3->den / r1.den * r1.num) + (r3->den / r2.den * r2.num);
  *r3 = simplifica_r (*r3);
  if (r3->num == 0)
     return 0;

  return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2)){
     r3->den = 0;
     return 0;
  }
  r3->den = mmc (r1.den, r2.den);
  r3->num = (r3->den / r1.den * r1.num) - (r3->den / r2.den * r2.num);
  *r3 = simplifica_r (*r3);
  if (r3->num == 0)
     return 0;

  return 1;
}


int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2)){
     r3->den = 0;
     return 0;
  }
  r3->den = r1.den * r2.den;
  r3->num = r1.num * r2.num;
  *r3 = simplifica_r (*r3);
  if (r3->num == 0)
     return 0;

  return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2)){
     r3->den = 0;
     return 0;
  }
  r3->den = r1.den * r2.num;
  r3->num = r1.num * r2.den;
  *r3 = simplifica_r (*r3);
  if (r3->num == 0)
     return 0;

  return 1;
}