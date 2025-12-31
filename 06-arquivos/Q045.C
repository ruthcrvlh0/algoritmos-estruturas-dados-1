#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Personagem {
    char nome[50];
    int nivel;
    float vida;
    float mana;
};

void criar_personagem() {
    struct Personagem novoPersonagem;
    FILE *arquivo = NULL;

    printf("\n--- Criacao de Novo Personagem ---\n");
    
    printf("Nome (max 49 caracteres): ");
    scanf("%s", novoPersonagem.nome); 
    
    printf("Nivel: ");
    scanf("%d", &novoPersonagem.nivel);

    printf("Vida Atual: ");
    scanf("%f", &novoPersonagem.vida);

    printf("Mana Atual: ");
    scanf("%f", &novoPersonagem.mana);

    arquivo = fopen("savegame.sav", "ab");

    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir/criar o arquivo savegame.sav.\n");
        return;
    }

    fwrite(&novoPersonagem, sizeof(struct Personagem), 1, arquivo);

    fclose(arquivo);

    printf("\n[SUCESSO] Personagem '%s' salvo no arquivo binario 'savegame.sav'.\n", novoPersonagem.nome);
}

int main() {
    int opcao;

    printf("--- Sistema de Save Game Binario ---\n");
    do {
        printf("\nMenu:\n");
        printf("1 - Criar Novo Personagem\n");
        printf("2 - Sair\n");
        printf("Escolha a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); 
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1:
                criar_personagem();
                break;
            case 2:
                printf("\nSaindo do sistema. Arquivo savegame.sav mantido.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 2);

    return 0;
}