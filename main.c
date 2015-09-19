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
        return 1;
    }
}

int doMove(int last_move, struct disco *v1, struct disco *v2) {

}

void hanoi(int n) {

    // cria as torres com base no tamanho informado
    struct disco tower[n],
            tower_aux[n],
            tower_final[n];

    struct disco discoNull = {-1, -1, -1, -1, -1};

    int i, n_real = n - 1, last_move = 0, pos;

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

    while (tower_final[n_real].value != -1) {
        if (last_move == 2) {
            pos = lastDiscTower(tower, n_real);
            // realizar mudança de acordo com o proximo que a estrutura do disco indica
            if (tower[pos].anilha_next ==) {

            }
            if (verificaMovimento(tower, tower_final, n_real)) {
                if (tower[pos].anilha_last)
                    doMove(last_move,);
            }
        } else if (last_move == 3) {

        }

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
