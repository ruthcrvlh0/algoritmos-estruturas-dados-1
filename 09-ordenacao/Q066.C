#include <stdio.h>
#include <stdlib.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortDecrescente(int arr[], int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                trocar(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int N;
    int i;
    int *pontuacoes = NULL;

    printf("--- Ordenacao do Placar de Batalha (Bubble Sort) ---\n");

    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    pontuacoes = (int *)malloc(N * sizeof(int));
    if (pontuacoes == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite as %d pontuacoes separadas por espaco: ", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &pontuacoes[i]);
    }

    bubbleSortDecrescente(pontuacoes, N);

    printf("\nPlacar Ordenado (Maior para a Menor Pontuacao):\n");
    for (i = 0; i < N; i++) {
        printf("%d ", pontuacoes[i]);
    }
    printf("\n");

    free(pontuacoes);
    pontuacoes = NULL;

    return 0;
}