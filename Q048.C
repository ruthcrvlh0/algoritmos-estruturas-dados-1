#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int vida;
    int ataque;
} Campeao;

#define TAMANHO_ESQUADRAO 3

void criar_arquivo_squad_dat() {
    Campeao dados_teste[TAMANHO_ESQUADRAO] = {
        {"Garen", 620, 69},
        {"Lux", 530, 55},
        {"Ashe", 590, 61}
    };
    
    FILE *f = fopen("squad.dat", "wb");
    if (f) {
        fwrite(dados_teste, sizeof(Campeao), TAMANHO_ESQUADRAO, f);
        fclose(f);
        printf("Arquivo squad.dat de teste criado. Execute o main novamente.\n");
    } else {
        printf("Erro ao criar arquivo de teste squad.dat.\n");
    }
}

int main() {
    Campeao esquadrao[TAMANHO_ESQUADRAO];
    Campeao tanque;
    FILE *arquivo = NULL;
    int i;
    arquivo = fopen("squad.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo squad.dat nao encontrado. Criando arquivo de teste...\n");
        criar_arquivo_squad_dat();
        return 0; 
    }

    size_t itens_lidos = fread(esquadrao, sizeof(Campeao), TAMANHO_ESQUADRAO, arquivo);

    if (itens_lidos != TAMANHO_ESQUADRAO) {
        printf("Erro na leitura: Esperados %d campeoes, lidos %zu.\n", TAMANHO_ESQUADRAO, itens_lidos);
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo);

    printf("--- Carregamento de Esquadrao Binario ---\n");
    printf("Esquadrao carregado com sucesso.\n");

    tanque = esquadrao[0]; 

    for (i = 1; i < TAMANHO_ESQUADRAO; i++) {
        if (esquadrao[i].vida > tanque.vida) {
            tanque = esquadrao[i];
        }
    }

    printf("\n--- Analise do Esquadrao ---\n");
    printf("%s: Tanque do esquadrão.\n", tanque.nome);

    return 0;
}
