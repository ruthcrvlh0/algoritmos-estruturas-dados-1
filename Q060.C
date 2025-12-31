#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int hp;
} Monstro;

int main() {
    int N;
    int i;
    Monstro alvo_mais_fraco;
    Monstro *horda = NULL;

    printf("--- Analise de Horda Inimiga ---\n");

    printf("Digite a quantidade de monstros na horda (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    horda = (Monstro *)malloc(N * sizeof(Monstro));
    if (horda == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    printf("\n--- Cadastro dos Monstros ---\n");
    for (i = 0; i < N; i++) {
        printf("Monstro %d (Nome HP): ", i + 1);
        scanf("%s %d", horda[i].nome, &horda[i].hp);
    }

    alvo_mais_fraco = horda[0]; 

    for (i = 1; i < N; i++) {
        if (horda[i].hp < alvo_mais_fraco.hp) {
            alvo_mais_fraco = horda[i];
        }
    }

    printf("\n--- Resultado da Analise ---\n");
    printf("Alvo prioritario: %s (%d HP)\n", alvo_mais_fraco.nome, alvo_mais_fraco.hp);

    free(horda);
    horda = NULL;

    return 0;
}