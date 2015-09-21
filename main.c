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

void printTowers(struct disco *v1, struct disco *v2, struct disco *v3, int n_real) {
    int i;
    printf("torre 1\t\t torre 2\t torre 3\n\n");
    for (i = n_real; i >= 0; i--) {
        printf("%d : %d\t\t %d : %d\t\t %d : %d\n", i, v1[i].value, i, v2[i].value, i, v3[i].value);
    }
}

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
        if (tower[i].value == -1 && i == 0) {
            return -1;
        } else if (tower[i].value == -1) {
            return i - 1;
        }
    }
    return -1;
}

/* ** verifica se há a possibilidade de passar da torre1 para a torre2 ** */
int verificaMovimento(struct disco *v1, struct disco *v2, int n_real) {
    int pos1 = lastDiscTower(v1, n_real);
    int pos2 = lastDiscTower(v2, n_real);

    pos2 = (pos2 == -1) ? 0 : pos2;
    if ((v2[pos2].value == -1 || v1[pos1].value < v2[pos2].value) && v1[pos1].value != -1) {
        if (v1[pos1].anilha_next == v2[pos2].anilha_current || v1[pos1].anilha_next == -1) {
            return 1;
        }
    }
    return 0;
}

void doMove(struct disco *v1, struct disco *v2, struct disco *v3, int n_real) {
    int last1, last2, last3;
    struct disco discoNull = {-1, -1, -1, -1};

    last1 = lastDiscTower(v1, n_real);
    last2 = lastDiscTower(v2, n_real);
    last3 = lastDiscTower(v3, n_real);

    if (verificaMovimento(v1, v2, n_real)) {
        printf("torre1 pra torre2\n");
        v1[last1].anilha_current = 2;
        v1[last1].anilha_last = 1;
        v1[last1].anilha_next = 3;

        v2[last2 + 1] = v1[last1];
        discoNull.anilha_current = 1;
        v1[last1] = discoNull;

    } else if (verificaMovimento(v1, v3, n_real)) {
        printf("torre1 pra torre3\n");
        v1[last1].anilha_current = 3;
        v1[last1].anilha_last = 1;
        v1[last1].anilha_next = 2;

        v3[last3 + 1] = v1[last1];
        discoNull.anilha_current = 1;
        v1[last1] = discoNull;

    } else if (verificaMovimento(v3, v2, n_real)) {
        printf("torre3 pra torre2\n");
        v3[last3].anilha_current = 2;
        v3[last3].anilha_last = 3;
        v3[last3].anilha_next = 1;

        v2[last2 + 1] = v3[last3];

        discoNull.anilha_current = 3;
        v3[last3] = discoNull;
    } else if (verificaMovimento(v3, v1, n_real)) {
        printf("torre3 pra torre1\n");
        v3[last3].anilha_current = 1;
        v3[last3].anilha_last = 3;
        v3[last3].anilha_next = 2;

        v1[last1 + 1] = v3[last3];
        discoNull.anilha_current = 3;
        v2[last3] = discoNull;

    } else if (verificaMovimento(v2, v3, n_real)) {
        printf("torre2 pra torre3\n");
        v2[last2].anilha_current = 3;
        v2[last2].anilha_last = 2;
        v2[last2].anilha_next = 1;

        v3[last3 + 1] = v2[last2];

        discoNull.anilha_current = 2;
        v2[last2] = discoNull;

    } else if (verificaMovimento(v2, v1, n_real)) {
        printf("torre2 pra torre1\n");
        v2[last2].anilha_current = 1;
        v2[last2].anilha_last = 2;
        v2[last2].anilha_next = 3;

        v1[last1 + 1] = v2[last2];

        discoNull.anilha_current = 2;
        v2[last2] = discoNull;
    }
}

void hanoi(int n) {

    // cria as torres com base no tamanho informado
    struct disco tower[n],
            tower_aux[n],
            tower_final[n];

    struct disco discoNull = {-1, -1, -1, -1};

    int n_real = n - 1, last_move = 0, count = 1;

    inicializa(tower, tower_aux, tower_final, n_real);

    /**  inicializando ordenacao  **/

    // primeiro passo
    if (n % 2 == 0) {
        tower[n_real].anilha_last = 1;
        tower[n_real].anilha_next = 3;
        tower[n_real].anilha_current = 2;

        tower_aux[0] = tower[n_real];
        last_move = 2;
    } else {

        tower[n_real].anilha_last = 1;
        tower[n_real].anilha_next = 2;
        tower[n_real].anilha_current = 3;

        tower_final[0] = tower[n_real];
        last_move = 3;
    }

    discoNull.anilha_current = 1;
    tower[n_real] = discoNull;

    while (tower_final[n_real].value == -1) {
        if (count == 6) {
            printTowers(tower, tower_aux, tower_final, n_real);
            return;
        }

        doMove(tower, tower_aux, tower_final, n_real);
        count++;
    }
    printf("parece q deu aqui\n\n\n");
    printTowers(tower, tower_aux, tower_final, n_real);
    return;
}

int main(int argc, char** argv) {
    int n;

    // lendo o tamanho da torre
    printf("INFORME O TAMANHO DA TORRE\n");
    scanf("%d", &n);

    hanoi(n);


    return (EXIT_SUCCESS);
}
