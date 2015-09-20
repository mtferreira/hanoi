/*
 * File:   main.c
 * Author: matheus-ferreira
 *
 * Created on 12 de Setembro de 2015, 22:34
 */

#include <stdio.h>
#include <stdlib.h>

/*Criando estrutura disco */
struct disco {
    int value;
    int anilha_current;
    int anilha_last;
    int anilha_next;
};

void print(struct disco v1, struct disco v2) {
    printf("movendo de %d para %d\n com dados:\n", v1.anilha_current, v2.anilha_current);
    printf("valor: %d\n atual: %d\n ultima %d\n proxima: %d\n", v1.value, v1.anilha_current, v1.anilha_last, v1.anilha_next);
}

void inicializa(struct disco *tower, struct disco *tower_aux, struct disco *tower_final, int n_real) {

    int i;

    for (i = n_real; i >= 0; i--) {

        tower[i].value = n_real - i;
        tower[i].anilha_current = 1;
        tower[i].anilha_last = -1;
        tower[i].anilha_next = -1;

        tower_aux[i].value = -1;
        tower_aux[i].anilha_current = 2;
        tower_aux[i].anilha_last = 1;
        tower_aux[i].anilha_next = -1;

        tower_final[i].value = -1;
        tower_final[i].anilha_current = 3;
        tower_final[i].anilha_last = 1;
        tower_final[i].anilha_next = -1;
    }
}

int lastDiscTower(struct disco *tower, int n_real) {
    int i;
    for (i = 0; i <= n_real; i++) {
        printf("%d: %d\n", i, tower[i].value);
        if (tower[i].value == -1) {
            return i - 1;
        }
    }
    return 0;
}

/* ** verifica se há a possibilidade de passar da torre1 para a torre2 ** */
int verificaMovimento(struct disco *v1, struct disco *v2, int n_real) {
    int pos1 = lastDiscTower(v1, n_real);
    int pos2 = lastDiscTower(v2, n_real);

    if (v2[pos2].value == -1 || v1[pos1].value < v2[pos2].value) {
        if (v1[pos1].anilha_next == v2[pos2].anilha_current || v1[pos1].anilha_next == -1) {
            return 1;
        }
    }
    return 0;
}

void hanoi(int n) {

    // cria as torres com base no tamanho informado
    struct disco tower[n],
            tower_aux[n],
            tower_final[n];

    struct disco discoNull = {-1, -1, -1, -1};

    int i, n_real = n - 1,
            last_move = 0,
            last1,
            last2,
            last3;

    inicializa(tower, tower_aux, tower_final, n_real);

    /**  inicializando ordenacao  **/

    // primeiro passo
    if (n % 2 == 0) {
        tower_aux[0].value = tower[n_real].value;
        tower_aux[0].anilha_last = 1;
        tower_aux[0].anilha_next = 3;
        tower_aux[0].anilha_current = 2;
        last_move = 2;
    } else {
        tower_final[0].value = tower[n_real].value;
        last_move = 3;
    }
    tower[n_real].value = -1;

    while (tower_final[n_real].value == -1) {
        last1 = lastDiscTower(tower, n_real);
        last2 = lastDiscTower(tower_aux, n_real);
        last3 = lastDiscTower(tower_final, n_real);
        printf("%d\n%d\n%d\n", last1, last2, last3);
        if (last_move == 2) {
            if (verificaMovimento(tower, tower_final, n_real)) {
                tower[last1].anilha_current = 3;
                tower[last1].anilha_last = 1;
                tower[last1].anilha_next = 2;
                //                print(tower[last1], tower_final[last3 + 1]);
                tower_final[last3 + 1] = tower[last1];
                discoNull.anilha_current = 1;
                tower[last1] = discoNull;
                last_move = 3;
            } else if (verificaMovimento(tower_final, tower, n_real)) {
                tower_final[last3].anilha_current = 1;
                tower_final[last3].anilha_last = 3;
                tower_final[last3].anilha_next = 2;

                tower[last1 + 1] = tower_final[last3];
                discoNull.anilha_current = 3;
                tower_final[last3] = discoNull;
                last_move = 1;
            } else if (verificaMovimento(tower, tower_aux, n_real)) {
                tower[last1].anilha_current = 2;
                tower[last1].anilha_last = 1;
                tower[last1].anilha_next = 3;

                tower_aux[last2 + 1] = tower[last1];
                discoNull.anilha_current = 1;
                tower[last1] = discoNull;
                last_move = 2;
            }
        } else if (last_move == 3) {
            if (verificaMovimento(tower, tower_aux, n_real)) {
                tower[last1].anilha_current = 2;
                tower[last1].anilha_last = 1;
                tower[last1].anilha_next = 3;

                tower_aux[last2 + 1] = tower[last1];
                discoNull.anilha_current = 1;
                tower[last1] = discoNull;
                last_move = 2;
            } else if (verificaMovimento(tower_aux, tower_final, n_real)) {
                tower_aux[last2].anilha_current = 3;
                tower_aux[last2].anilha_last = 2;
                tower_aux[last2].anilha_next = 1;

                tower_final[last3 + 1] = tower_aux[last2];
                discoNull.anilha_current = 2;
                tower_aux[last2] = discoNull;
                last_move = 3;
            }
        } else if (last_move == 1) {
            if (verificaMovimento(tower_final, tower_aux, n_real)) {
                tower_final[last3].anilha_current = 2;
                tower_final[last3].anilha_last = 3;
                tower_final[last3].anilha_next = 1;

                tower_aux[last2 + 1] = tower_final[last3];
                discoNull.anilha_current = 3;
                tower_final[last3] = discoNull;
                last_move = 2;
            }
        }
    }
    printf("parece q deu aqui\n\n\n");
    for (i = 0; i <= n_real; i++) {
        printf("%d : %d\n", i, tower_final[i].value);
    }
}

int main(int argc, char** argv) {
    int n;

    // lendo o tamanho da torre
    printf("INFORME O TAMANHO DA TORRE\n");
    scanf("%d", &n);

    hanoi(n);


    return (EXIT_SUCCESS);
}
