#include <stdio.h>
#include <stdlib.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Implementa a função de Partição (do Quick Sort) de forma in-place.
 * Reorganiza o vetor v em torno do pivô (v[n-1]).
 * Todos os elementos menores ou iguais ao pivô são movidos para o início.
 * Todos os elementos maiores que o pivô são movidos para o final.
 * * @param n O tamanho do vetor.
 * @param v O vetor de pontos de vida (entrada e saída).
 * @return O índice final onde o pivô foi posicionado.
 */

int particao_in_place(int n, int v[]) {
    if (n <= 1) {
        return n > 0 ? 0 : -1; 
    }

    int pivo = v[n - 1]; 
    int i = -1; 
    
    for (int j = 0; j < n - 1; j++) {
        if (v[j] <= pivo) {
            i++;
            trocar(&v[i], &v[j]);
        }
    }

    trocar(&v[i + 1], &v[n - 1]);
    return i + 1;
}

int main() {
    int n;
    int i;
    int *v = NULL;

    printf("--- Triagem de Unidades Mecha (Particao In-Place) ---\n");

    printf("Digite a quantidade de unidades mecha (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    v = (int *)malloc(n * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d pontos de vida separados por espaco: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    printf("\nO limite de dano (pivo) e: %d\n", v[n - 1]);

    int indice_pivo = particao_in_place(n, v);

    printf("\nUnidades Reorganizadas (Triagem):\n");
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("\n[INFO] O pivo (%d) foi posicionado no indice %d.\n", v[indice_pivo], indice_pivo);
    
    free(v);
    v = NULL;

    return 0;
}