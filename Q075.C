#include <stdio.h>
#include <stdlib.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Particiona o array em torno de um pivô (o último elemento).
 * Coloca todos os elementos menores ou iguais ao pivô à esquerda, e os maiores à direita.
 * @param arr O array a ser particionado.
 * @param p O índice de início do segmento.
 * @param r O índice de fim do segmento (onde o pivô se encontra).
 * @return O índice final onde o pivô foi posicionado.
 */

int particao(int arr[], int p, int r) {
    int pivo = arr[r];
    int i = (p - 1);   


    for (int j = p; j <= r - 1; j++) {
        if (arr[j] <= pivo) {
            i++; 
            trocar(&arr[i], &arr[j]); 
        }
    }
    
    trocar(&arr[i + 1], &arr[r]);
    
    return (i + 1);
}

/**
 * @brief Função principal do Quick Sort.
 * @param arr O array a ser ordenado.
 * @param p O índice de início do segmento.
 * @param r O índice de fim do segmento.
 */
void quickSort(int arr[], int p, int r) {
    if (p < r) {
        int pi = particao(arr, p, r);

        quickSort(arr, p, pi - 1); 
        quickSort(arr, pi + 1, r); 
    }
}

int main() {
    int N;
    int i;
    int *mmr = NULL;

    printf("--- Ordenacao de Jogadores por MMR (Quick Sort) ---\n");

    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    mmr = (int *)malloc(N * sizeof(int));
    if (mmr == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d MMRs separados por espaco: ", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &mmr[i]);
    }

    quickSort(mmr, 0, N - 1);

    printf("\nMMRs Ordenados (Prontos para Matchmaking):\n");
    for (i = 0; i < N; i++) {
        printf("%d ", mmr[i]);
    }
    printf("\n");

    free(mmr);
    mmr = NULL;

    return 0;
}