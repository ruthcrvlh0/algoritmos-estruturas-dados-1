#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int eliminacoes; 
} Jogador;

void trocar_jogadores(Jogador *a, Jogador *b) {
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSortDecrescente(Jogador arr[], int n) {
    int i, j, indice_maximo;

    for (i = 0; i < n - 1; i++) {
        indice_maximo = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].eliminacoes > arr[indice_maximo].eliminacoes) {
                indice_maximo = j;
            }
        }
        if (indice_maximo != i) {
            trocar_jogadores(&arr[indice_maximo], &arr[i]);
        }
    }
}

int main() {
    int N, i;
    Jogador *leaderboard = NULL;

    printf("--- Criando Leaderboard (Selection Sort Decrescente) ---\n");
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

    for (i = 0; i < N; i++) {
        printf("Jogador %d (Nome Kills): ", i + 1);
        scanf("%s %d", leaderboard[i].nome, &leaderboard[i].eliminacoes);
    }

    selectionSortDecrescente(leaderboard, N);

    printf("\n--- Leaderboard Final ---\n");
    for (i = 0; i < N; i++) {
        printf("%s: %d eliminacoes\n", leaderboard[i].nome, leaderboard[i].eliminacoes);
    }

    free(leaderboard); 
    leaderboard = NULL;
    
    return 0;
}