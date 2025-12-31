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

void bubbleSortDecrescente(Jogador arr[], int n) {
    int i, j;
    

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {

            if (arr[j].pontuacao < arr[j + 1].pontuacao) {
                trocar(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int N;
    int i;
    Jogador *leaderboard = NULL;

    printf("--- Leaderboard da Arena de Batalha (Bubble Sort Decrescente) ---\n");

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

    printf("Digite o ID e a pontuacao de cada um dos %d jogadores:\n", N);
    for (i = 0; i < N; i++) {
        printf("Jogador %d (ID Pontuacao): ", i + 1);
        scanf("%d %d", &leaderboard[i].id, &leaderboard[i].pontuacao);
    }

    bubbleSortDecrescente(leaderboard, N);

    printf("\n--- Placar Final Ordenado ---\n");
    for (i = 0; i < N; i++) {
        printf("%d %d\n", leaderboard[i].id, leaderboard[i].pontuacao);
    }

    free(leaderboard);
    leaderboard = NULL;

    return 0;
}