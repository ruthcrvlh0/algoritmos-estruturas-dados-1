#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int pontuacao;
} Jogador;

void trocar(Jogador *a, Jogador *b) {
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Particiona o array em torno do pivô (o último elemento).
 * Coloca todos os elementos MAIORES ou iguais ao pivô à esquerda.
 * @param arr O vetor de Jogadores a ser particionado.
 * @param p O índice de início do segmento.
 * @param r O índice de fim do segmento (pivô).
 * @return O índice final onde o pivô foi posicionado.
 */
 
int particao(Jogador arr[], int p, int r) {
    int pivo_pontuacao = arr[r].pontuacao; 
    int i = (p - 1); 

    for (int j = p; j <= r - 1; j++) {

        if (arr[j].pontuacao >= pivo_pontuacao) {
            i++; 
            trocar(&arr[i], &arr[j]); 
        }
    }
    
    trocar(&arr[i + 1], &arr[r]);
    
    return (i + 1);
}

/**
 * @brief Função principal do Quick Sort.
 * @param arr O vetor de Jogadores a ser ordenado.
 * @param p O índice de início do segmento.
 * @param r O índice de fim do segmento.
 */

void quickSort(Jogador arr[], int p, int r) {
    if (p < r) {
        int pi = particao(arr, p, r);

        quickSort(arr, p, pi - 1); 
        quickSort(arr, pi + 1, r); 
    }
}

int main() {
    int N;
    int i;
    Jogador *leaderboard = NULL;

    printf("--- Leaderboard com Quick Sort Decrescente ---\n");

    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    leaderboard = (Jogador *)malloc(N * sizeof(Jogador));
    if (leaderboard == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite o ID e a Pontuacao de cada um dos %d jogadores:\n", N);
    for (i = 0; i < N; i++) {
        printf("Jogador %d (ID Pontuacao): ", i + 1);
        scanf("%d %d", &leaderboard[i].id, &leaderboard[i].pontuacao);
    }

    quickSort(leaderboard, 0, N - 1);

    printf("\n--- Placar Final Ordenado (Maior Pontuacao Primeiro) ---\n");
    for (i = 0; i < N; i++) {
        printf("%d %d\n", leaderboard[i].id, leaderboard[i].pontuacao);
    }

    free(leaderboard);
    leaderboard = NULL;

    return 0;
}