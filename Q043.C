#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int vida;
    int ataque;
} Inimigo;

int main() {
    FILE *arquivo = NULL;
    Inimigo inimigo_atual;
    Inimigo maior_ameaca;
    int primeiro_inimigo = 1;

    printf("--- Analise da Onda de Ataque ---\n");

    arquivo = fopen("wave_data.txt", "r");

    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo wave_data.txt. Verifique o caminho.\n");
        return 1;
    }

    printf("Arquivo de onda carregado com sucesso.\n");
    while (fscanf(arquivo, "%s %d %d", 
                  inimigo_atual.nome, 
                  &inimigo_atual.vida, 
                  &inimigo_atual.ataque) == 3) {
        if (primeiro_inimigo) {
            maior_ameaca = inimigo_atual;
            primeiro_inimigo = 0;
            continue; 
        }
        if (inimigo_atual.ataque > maior_ameaca.ataque) {
            maior_ameaca = inimigo_atual;
        }
    }

    fclose(arquivo);

    if (!primeiro_inimigo) {
        printf("\n--- Resultado da Analise ---\n");
        printf("Maior Ameaca: %s, Vida: %d, Ataque: %d\n", 
               maior_ameaca.nome, maior_ameaca.vida, maior_ameaca.ataque);
    } else {
        printf("\nO arquivo de onda estava vazio ou em formato incorreto.\n");
    }

    return 0;
}