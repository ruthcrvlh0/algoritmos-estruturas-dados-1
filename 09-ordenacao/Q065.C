#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

void insertionSortDecrescente(Jogador arr[], int n) {
    int i, j;
    Jogador chave;

    for (i = 1; i < n; i++) {
        chave = arr[i]; 
        j = i - 1;      

        while (j >= 0 && arr[j].pontuacao < chave.pontuacao) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

int main() {
    int N;
    int i;
    Jogador *leaderboard = NULL;

    printf("--- Leaderboard de Pontuacao (Insertion Sort Decrescente) ---\n");

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

    printf("--- Cadastro dos Jogadores (Nome Pontuacao) ---\n");
    for (i = 0; i < N; i++) {
        printf("Jogador %d: ", i + 1);
        scanf("%s %d", leaderboard[i].nome, &leaderboard[i].pontuacao);
    }

    insertionSortDecrescente(leaderboard, N);

    printf("\n--- Ranking Final ---\n");
    for (i = 0; i < N; i++) {
        printf("%d %s\n", leaderboard[i].pontuacao, leaderboard[i].nome);
    }
    
    free(leaderboard);
    leaderboard = NULL;

    return 0;
}