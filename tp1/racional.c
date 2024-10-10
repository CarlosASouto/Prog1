/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

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
  else
    return mdc (b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return ((a * b) / mdc (a, b));
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
  return simplifica_r (r);
}

int valido_r (struct racional r)
{
  if (r.den == 0)
    return 0;
  return 1;
}

struct racional sorteia_r (long min, long max)
{
  struct racional r;
  r.num = aleat (min, max);
  r.den = aleat (min, max);
  return simplifica_r (r);
}

void imprime_r (struct racional r)
{
  if (r.num == 0 || r.den == 1)
    printf ("%ld ", r.num);
  else
    if (r.num == r.den)
      printf ("1 ");
    else
      if (!valido_r (r))
        printf ("INVALIDO ");
      else
        printf ("%ld/%ld ", r.num, r.den);
}

struct racional soma_r (struct racional r1, struct racional r2)
{
  struct racional r;
  if (!valido_r (r1) || !valido_r (r2)){
    r.den = 0;
    return r;
  }
  r.den = mmc (r1.den, r2.den);
  r.num = (r.den / r1.den * r1.num) + (r.den / r2.den * r2.num);
  return simplifica_r (r);
}

struct racional subtrai_r (struct racional r1, struct racional r2)
{
  struct racional r;
  if (!valido_r (r1) || !valido_r (r2)){
    r.den = 0;
    return r;
  }
  r.den = mmc (r1.den, r2.den);
  r.num = (r.den / r1.den * r1.num) - (r.den / r2.den * r2.num);
  return simplifica_r (r);
}

struct racional multiplica_r (struct racional r1, struct racional r2)
{
  struct racional r;
  if (!valido_r (r1) || !valido_r (r2)){
    r.den = 0;
    return r;
  }
  r.den = r1.den * r2.den;
  r.num = r1.num * r2.num;
  return simplifica_r (r);
}

struct racional divide_r (struct racional r1, struct racional r2)
{
  struct racional r;
  if (!valido_r (r1) || !valido_r (r2)){
    r.den = 0;
    return r;
}
r.den = r1.den * r2.num;
r.num = r1.num * r2.den;
return simplifica_r (r);
}