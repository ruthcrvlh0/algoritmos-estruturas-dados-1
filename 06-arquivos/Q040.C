#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Jogador {
    char nome[50];
    int pontuacao;
};

int main() {
    int n, i;
    struct Jogador *jogadores = NULL;
    struct Jogador recordista;
    FILE *arquivo = NULL;

    printf("--- Nitro Dash: Salvando Recorde ---\n");
    printf("Digite a quantidade de jogadores na partida (n): ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    jogadores = (struct Jogador *)malloc(n * sizeof(struct Jogador));
    if (jogadores == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nJogador %d:\n", i + 1);
        printf(" Nome: ");
        scanf("%s", jogadores[i].nome);
        printf(" Pontuacao: ");
        scanf("%d", &jogadores[i].pontuacao);
    }
    
    recordista = jogadores[0];
    
    for (i = 1; i < n; i++) {
        if (jogadores[i].pontuacao > recordista.pontuacao) {
            recordista = jogadores[i];
        }
    }

    arquivo = fopen("highscore.txt", "w");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir/criar o arquivo highscore.txt.\n");
        free(jogadores);
        return 1;
    }

    fprintf(arquivo, "Nome: %s, Pontuacao: %d\n", recordista.nome, recordista.pontuacao);

    fclose(arquivo);

    printf("\nRecorde salvo com sucesso em highscore.txt:\n");
    printf("Recordista: %s, Pontuacao: %d\n", recordista.nome, recordista.pontuacao);

    free(jogadores);
    jogadores = NULL;

    return 0;
}