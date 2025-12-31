#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// 1. Implementação da função recursiva de Divisão e Conquista
/**
 * @brief Encontra o valor máximo em um segmento de um array usando Divisão e Conquista.
 * @param fragmentos O vetor contendo os níveis de poder.
 * @param inicio O índice de início do segmento atual.
 * @param fim O índice de fim do segmento atual.
 * @return O maior valor encontrado no segmento [inicio...fim].
 */
int encontrar_maximo_divisao_e_conquista(const int fragmentos[], int inicio, int fim) {

    if (inicio == fim) {
        return fragmentos[inicio];
    }

    int meio = inicio + (fim - inicio) / 2;

    int max_esquerda = encontrar_maximo_divisao_e_conquista(fragmentos, inicio, meio);
    int max_direita = encontrar_maximo_divisao_e_conquista(fragmentos, meio + 1, fim);

    return max(max_esquerda, max_direita);
}

int main() {
    int N;
    int i;
    int *fragmentos = NULL;
    int poder_maximo;

    printf("--- Encontrando a Fonte de Poder Maxima (Divisao e Conquista) ---\n");

    printf("Digite a quantidade de Fragmentos de Alma (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    fragmentos = (int *)malloc(N * sizeof(int));
    if (fragmentos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d niveis de poder separados por espaco: ", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &fragmentos[i]);
    }

    poder_maximo = encontrar_maximo_divisao_e_conquista(fragmentos, 0, N - 1);

    printf("\n--- Resultado do Ritual ---\n");
    printf("O Fragmento de Alma mais poderoso tem nivel: %d\n", poder_maximo);

    free(fragmentos);
    fragmentos = NULL;

    return 0;
}