#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defina a struct para armazenar os dados de um inimigo
struct Inimigo {
    char nome[50];
    float hp;
    float atk;
};

int main() {
    struct Inimigo lista_inimigos[3];
    float nivel_ameaca;
    int i = 0;
    
    FILE *arquivo = NULL;

    // Abrir o arquivo para leitura
    arquivo = fopen("inimigos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo inimigos.txt\n");
        return 1;
    }

    printf("Lendo dados do arquivo...\n");
    
    while (fscanf(arquivo, "%s %f %f", 
                  lista_inimigos[i].nome, 
                  &lista_inimigos[i].hp, 
                  &lista_inimigos[i].atk) == 3 && i < 3) {
        i++;
    }

    fclose(arquivo);

    printf("\n--- Inimigos Elite (Nivel de Ameaça >= 200) ---\n");

    // Calcular o Nível de Ameaça e imprimir os inimigos "elite"
    for (int j = 0; j < i; j++) {
        nivel_ameaca = lista_inimigos[j].hp + lista_inimigos[j].atk;
        if (nivel_ameaca >= 200.0) {
            printf("Elite Encontrado: %s\n", lista_inimigos[j].nome);
            printf("  Nivel de Ameaca: %.1f\n", nivel_ameaca);
        }
    }

    if (i == 0) {
        printf("Nenhum dado de inimigo foi lido.\n");
    }

    return 0;
}