#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Conta recursivamente o número de cristais com carga positiva em um vetor.
 * * @param inventario O vetor de inteiros contendo os níveis de carga.
 * @param n O tamanho total do vetor.
 * @param indice O índice do elemento atual a ser verificado.
 * @return O número total de cristais com carga > 0.
 */
int contar_cristais_positivos(const int *inventario, int n, int indice) {

    if (indice >= n) {
        return 0;
    }

    int contribuicao_atual = 0;

    if (inventario[indice] > 0) {
        contribuicao_atual = 1;
    }

    return contribuicao_atual + contar_cristais_positivos(inventario, n, indice + 1);
}

int main() {
    int n, i;
    int *inventario = NULL;
    int total_feitiços;

    printf("--- Analise de Estoque de Cristais de Mana ---\n");

    printf("Digite o numero total de cristais no inventario (n): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    if (n == 0) {
        printf("Nenhum cristal para analisar. Feiticos disponiveis: 0\n");
        return 0;
    }

    inventario = (int *)malloc(n * sizeof(int));
    if (inventario == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d niveis de carga, separados por espaco:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &inventario[i]);
    }

    total_feitiços = contar_cristais_positivos(inventario, n, 0);

    printf("\n--- Resultado da Analise ---\n");
    printf("Total de cristais carregados (carga positiva): %d\n", total_feitiços);
    printf("O mago pode lancar %d feiticos.\n", total_feitiços);

    free(inventario);
    inventario = NULL;

    return 0;
}