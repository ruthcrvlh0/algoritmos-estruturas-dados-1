#include <stdio.h>

int main() {
    int sala_1[] = {10, 20, 5};
    int sala_2[] = {50, 100};
    int sala_3[] = {5, 5, 5, 10};

    int *ponteiro_salas[3];
    ponteiro_salas[0] = sala_1;
    ponteiro_salas[1] = sala_2;
    ponteiro_salas[2] = sala_3;

    int tamanho_sala_1 = sizeof(sala_1) / sizeof(sala_1[0]);
    int tamanho_sala_2 = sizeof(sala_2) / sizeof(sala_2[0]);
    int tamanho_sala_3 = sizeof(sala_3) / sizeof(sala_3[0]);

    printf("Moedas na Sala 1: ");
    for (int i = 0; i < tamanho_sala_1; i++) {
        printf("%d ", *(ponteiro_salas[0] + i));
    }
    printf("\n");

    printf("Moedas na Sala 2: ");
    for (int i = 0; i < tamanho_sala_2; i++) {
        printf("%d ", *(ponteiro_salas[1] + i));
    }
    printf("\n");

    printf("Moedas na Sala 3: ");
    for (int i = 0; i < tamanho_sala_3; i++) {
        printf("%d ", *(ponteiro_salas[2] + i));
    }
    printf("\n");

    return 0;
}