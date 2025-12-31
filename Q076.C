#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Seleciona um pivô aleatório e, em seguida, particiona o array.
 * @param arr O array a ser particionado.
 * @param p O índice de início do segmento.
 * @param r O índice de fim do segmento.
 * @return O índice final onde o pivô foi posicionado.
 */
int particao(int arr[], int p, int r) {

    int indice_aleatorio = p + rand() % (r - p + 1);
    trocar(&arr[indice_aleatorio], &arr[r]);

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
    int *scores = NULL;

    srand(time(NULL)); 

    printf("--- Quick Sort com Pivo Aleatorio para Leaderboard ---\n");

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

    quickSort(scores, 0, N - 1);

    printf("\nPontuacoes Ordenadas:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n");

    free(scores);
    scores = NULL;

    return 0;
}