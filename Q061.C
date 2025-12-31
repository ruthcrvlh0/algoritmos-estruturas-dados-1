#include <stdio.h>
#include <stdlib.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, indice_minimo;

    for (i = 0; i < n - 1; i++) {

        indice_minimo = i;

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice_minimo]) {
                indice_minimo = j;
            }
        }

        if (indice_minimo != i) {
            trocar(&arr[indice_minimo], &arr[i]);
        }
    }
}

int main() {
    int N;
    int i;
    int *scores = NULL;

    printf("--- High Score Sorter (Selection Sort) ---\n");

    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    scores = (int *)malloc(N * sizeof(int));
    if (scores == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite as %d pontuacoes separadas por espaco: ", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    selectionSort(scores, N);

    printf("\nScores Ordenados (Menor para o Maior):\n");
    for (i = 0; i < N; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n");
    
    free(scores);
    scores = NULL;

    return 0;
}