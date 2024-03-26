#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
/* acrescente demais includes que voce queira ou precise */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){
    return min + rand() % (max+1 - min);
}

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
/* dica: a versao recursiva eh bem elegante! */
int mdc (int a, int b){
    if (b==0)
        return a;
    else
        return mdc (b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
    return ((a * b) / mdc (a, b)); 
}

/* Recebe um numero racional e o retorna simplificado.
 * Por exemplo, ao receber 10/8 devera retornar 5/4.
 * Se ambos numerador e denominador forem negativos, devera retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Quem chama esta funcao deve garantir que o racional r eh valido */
void simplifica_r (struct racional *r){

}

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

int numerador_r (struct racional r){
    return r.num;
}

int denominador_r (struct racional r){
    return r.den;
}

int valido_r (struct racional r){
    return r.valido;
}

struct racional cria_r (int numerador, int denominador){

}

struct racional sorteia_r (int n){
    struct racional r;
    r.num = aleat (-n, n);
    r.den = aleat (-n, n);
    if (denominador_r (r) == 0)
        r.valido = 0;
    else
        r.valido = 1;
    if (valido_r)
        simplifica_r (r);
    return r;
}