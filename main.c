/*
 * File:   main.c
 * Author: matheus-ferreira
 *
 * Created on 12 de Setembro de 2015, 22:34
 */

#include <stdio.h>
#include <stdlib.h>

void hanoi(int n) {

    /*Criando estrutura disco */
    struct disco {
        int value;
        int anilha_current;
        int anilha_last;
        int anilha_next;
    };

    // cria as torres com base no tamanho informado
    struct disco tower[n] = {.value = -1, .anilha_current. = 1, .anilha_last = -1, .anilha_next = -1},
    tower_aux[n] = {-1, -1, -1, -1},
    tower_final[n] = {-1, -1, -1, -1};

    int i, n_real = n - 1;

    // inicializa a torre original
    for (i = 1; i >= n_real; i--) {
        tower[i].value = i;
        tower[i].anilha_current = 1;
    }

    for (i = n - 1; i >= 0; i--) {
        printf("posição %d : %d\n", i, tower[i]);
    }
    return;
    /**  inicializando ordenacao  **/

    // primeiro passo
    if (n % 2 == 0) {
        tower_aux[0].value = tower[n_real];
    } else {
        tower_final[0] = tower[n_real];
    }
    tower[n_real] = -1;

}

int main(int argc, char** argv) {
    int n;

    // lendo o tamanho da torre
    printf("INFORME O TAMANHO DA TORRE\n");
    scanf("%d", &n);

    hanoi(n);


    return (EXIT_SUCCESS);
}
