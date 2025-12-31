#include <stdio.h>
#include <string.h>

struct ItemColetavel {
    char nome[50];
    int valor_pontos;
};

int main() {
    struct ItemColetavel inventario[3];
    int i;

    printf("--- Simulacao de Inventario (3 Itens) ---\n");

    for (i = 0; i < 3; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Digite o nome do item: ");
        scanf("%s", inventario[i].nome);
        printf("Digite o valor em pontos: ");
        scanf("%d", &inventario[i].valor_pontos);
    }
    
    struct ItemColetavel mais_valioso = inventario[0];

    for (i = 1; i < 3; i++) {
        if (inventario[i].valor_pontos > mais_valioso.valor_pontos) {
            mais_valioso.valor_pontos = inventario[i].valor_pontos;
            strcpy(mais_valioso.nome, inventario[i].nome);
        }
    }

    printf("\n--- Analise do Inventario ---\n");
    printf("O item mais valioso coletado foi: %s (Valor: %d pontos)\n", 
           mais_valioso.nome, mais_valioso.valor_pontos);

    return 0;
}