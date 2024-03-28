#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
/* acrescente demais includes que voce queira ou precise */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){
    return ((rand() % (max - min + 1)) + min);
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
    int divisor = mdc (numerador_r (*r), denominador_r (*r));
    r->num = r->num / divisor;
    r->den = r->den / divisor;
    if (denominador_r (*r) < 0){
        r->num = numerador_r (*r) * -1;
        r->den = denominador_r (*r) * -1;
    }
}

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
    struct racional r;
    r.num = numerador;
    r.den = denominador;
    if (denominador == 0)
        r.valido = 0;
    else
        r.valido = 1;
    if (valido_r (r))
        simplifica_r (&r);
    return r;
}

struct racional sorteia_r (int n){
    struct racional r;
    r.num = aleat (-n, n);
    r.den = aleat (-n, n);
    if (denominador_r (r) == 0)
        r.valido = 0;
    else
        r.valido = 1;
    if (valido_r (r))
        simplifica_r (&r);
    return r;
}

void soma_r (struct racional r1, struct racional r2, struct racional *r3){
    if (valido_r (r1) && valido_r (r2))
        r3->valido = 1;
    else
        r3->valido = 0;
    r3->den = mmc (denominador_r (r1), denominador_r (r2));
    r3->num = (denominador_r (*r3) / denominador_r (r1) * numerador_r (r1)) + (denominador_r (*r3) / denominador_r (r2) * numerador_r (r2));
    simplifica_r (r3);
}
void subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
    if (valido_r (r1) && valido_r (r2))
        r3->valido = 1;
    else
        r3->valido = 0;
    r3->den = mmc (denominador_r (r1), denominador_r (r2));
    r3->num = (denominador_r (*r3) / denominador_r (r1) * numerador_r (r1)) - (denominador_r (*r3) / denominador_r (r2) * numerador_r (r2));
    simplifica_r (r3);
}
void multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
    if (valido_r (r1) && valido_r (r2))
        r3->valido = 1;
    else
        r3->valido = 0;
    r3->den = denominador_r (r1) * denominador_r (r2);
    r3->num = numerador_r (r1) * numerador_r (r2);
    simplifica_r (r3);
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){
    if (numerador_r (r2) == 0)
        r3->valido = 0;
    else
        r3->valido = 1;
    r3->den = denominador_r (r1) * numerador_r (r2);
    r3->num = numerador_r (r1) * denominador_r (r2);
    simplifica_r (r3);
    return valido_r (*r3);
}

int compara_r (struct racional r1, struct racional r2){
    r1.num = denominador_r (r2) * numerador_r (r1);
    r2.num = denominador_r (r1) * numerador_r (r2);
    if (numerador_r (r1) > numerador_r (r2))
        return 1;
    if (numerador_r (r1) < numerador_r (r2))
        return -1;
    else
        return 0;
}

void imprime_r (struct racional r){
    if ((numerador_r (r) == 0) || (denominador_r (r) == 1))
        printf ("%d", numerador_r (r));
    else
        if (numerador_r (r) == denominador_r (r))
            printf ("1");
        else
            if (!valido_r (r))
                printf ("INVALIDO");
            else
                printf("%d/%d", numerador_r (r), denominador_r (r));
}