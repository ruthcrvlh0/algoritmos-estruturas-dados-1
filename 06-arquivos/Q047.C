#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int vida;
    int ataque;
} Unidade;

int main() {
    int n, i;
    Unidade *esquadrao = NULL;
    Unidade unidade_mais_forte;
    FILE *arquivo = NULL;

    printf("--- Montagem e Salvamento do Esquadrao ---\n");
    printf("Quantas unidades terao no esquadrao (n): ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero de unidades invalido. Encerrando.\n");
        return 1;
    }

    esquadrao = (Unidade *)malloc(n * sizeof(Unidade));
    if (esquadrao == NULL) {
        printf("Erro: Falha ao alocar memoria para o esquadrao.\n");
        return 1;
    }

    printf("\n--- Cadastro das Unidades ---\n");
    for (i = 0; i < n; i++) {
        printf("Unidade %d:\n", i + 1);
        printf(" Nome (sem espacos): ");
        scanf("%s", esquadrao[i].nome);
        printf(" Vida (HP): ");
        scanf("%d", &esquadrao[i].vida);
        printf(" Ataque (ATK): ");
        scanf("%d", &esquadrao[i].ataque);
    }

    arquivo = fopen("squad.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir/criar o arquivo squad.dat.\n");
        free(esquadrao);
        return 1;
    }

    fwrite(esquadrao, sizeof(Unidade), n, arquivo);
    fclose(arquivo);
    printf("\n[SUCESSO] Esquadrao salvo em 'squad.dat' (%d unidades).\n", n);

    unidade_mais_forte = esquadrao[0];

    for (i = 1; i < n; i++) {
        if (esquadrao[i].ataque > unidade_mais_forte.ataque) {
            unidade_mais_forte = esquadrao[i];
        }
    }

    printf("\n--- Analise do Esquadrao ---\n");
    printf("A unidade com o maior Poder de Ataque (ATK=%d) e: %s\n", 
           unidade_mais_forte.ataque, unidade_mais_forte.nome);
    free(esquadrao);
    esquadrao = NULL;

    return 0;
}