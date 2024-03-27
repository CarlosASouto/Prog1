/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

int main (){
    int n, max;
    struct racional r1, r2, soma, sub, mult, div;
    srand(10);
    scanf ("%d", &n);
    scanf ("%d", &max);
    for (int i = 0; i < n; i++)
    {
        printf ("%d: ", i);
        r1 = sorteia_r (max);
        r2 = sorteia_r (max);
        imprime_r (r1);
        printf (" ");
        imprime_r (r2);
        if (!valido_r (r1) || !valido_r (r2)){
            printf (" NUMERO INVALIDO");
            return 1;
        }
        soma_r (r1, r2, &soma);
        subtrai_r (r1, r2, &sub);
        multiplica_r (r1, r2, &mult);
        if (!divide_r (r1, r2, &div)){
            printf("DIVISAO INVALIDA");
            return 1;
        }
        imprime_r (soma);
        printf (" ");
        imprime_r (sub);
        printf (" ");
        imprime_r (mult);
        printf (" ");
        imprime_r (div);
        printf ("\n");
    }
    
    return 0;
}
