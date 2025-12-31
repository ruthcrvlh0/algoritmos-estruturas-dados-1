#include <stdio.h>
#include <stdlib.h>

struct Inimigo {
    char tipo[50];
    int hp;
};

int main() {
    int n, i;

    printf("--- Relatorio de Reconhecimento Inimigo ---\n");

    printf("Digite o numero de unidades inimigas (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero de unidades invalido. Encerrando.\n");
        return 1;
    }

    printf("\n--- Leitura dos Dados ---\n");
    
    struct Inimigo *esquadrao = (struct Inimigo *)malloc(n * sizeof(struct Inimigo));
    if (esquadrao == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Unidade %d:\n", i + 1);
        
        printf(" Tipo (ex: Orc, Goblin): ");
        scanf("%s", esquadrao[i].tipo);
        
        printf(" Pontos de Vida (HP): ");
        scanf("%d", &esquadrao[i].hp);

        printf("RELATORIO: Inimigo: %s, HP: %d\n", esquadrao[i].tipo, esquadrao[i].hp);
        printf("\n");
    }

    free(esquadrao);
    esquadrao = NULL;
    printf("Analise do esquadrao inimigo concluida.\n");
    
    return 0;
}