#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PlayerProfile {
    char nome[50];
    int nivel;
    int highScore;
};

void ler_e_rankear_perfis() {
    FILE *arquivo = NULL;
    struct PlayerProfile perfil_atual;
    char *rank;

    arquivo = fopen("profiles.dat", "rb");

    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo profiles.dat.\n");
        printf("Execute o codigo auxiliar para criar o arquivo de teste primeiro.\n");
        return;
    }

    printf("--- Carregamento e Ranking de Perfis ---\n");

    while (fread(&perfil_atual, sizeof(struct PlayerProfile), 1, arquivo) == 1) {

        // Determinar e atribuir o Rank
        if (perfil_atual.highScore > 10000) {
            rank = "Mestre do Jogo";
        } else if (perfil_atual.highScore > 5000) {
            rank = "Veterano";
        } else {
            rank = "Aspirante";
        }
        printf("Nome: %s, Score: %d, Rank: %s\n", 
               perfil_atual.nome, perfil_atual.highScore, rank);
    }

    fclose(arquivo);
    printf("\nLeitura do arquivo concluida.\n");
}

int main() {
    ler_e_rankear_perfis();
    
    return 0;
}