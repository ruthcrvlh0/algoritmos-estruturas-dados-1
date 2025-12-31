#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Intercala dois vetores ordenados (arr1 e arr2) em um terceiro vetor (resultado).
 * @param arr1 O primeiro vetor ordenado.
 * @param n O tamanho do primeiro vetor.
 * @param arr2 O segundo vetor ordenado.
 * @param m O tamanho do segundo vetor.
 * @param resultado O vetor de saída, de tamanho n + m.
 */
void intercalar_vetores(const int arr1[], int n, const int arr2[], int m, int resultado[]) {
    int i = 0; 
    int j = 0; 
    int k = 0; 

    while (i < n && j < m) {
        if (arr1[i] <= arr2[j]) {
            resultado[k] = arr1[i];
            i++;
        } else {
            resultado[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < n) {
        resultado[k] = arr1[i];
        i++;
        k++;
    }

    while (j < m) {
        resultado[k] = arr2[j];
        j++;
        k++;
    }
}

int main() {
    int n, m;
    int i;
    int *alfa = NULL;
    int *beta = NULL;
    int *unificado = NULL;

    printf("--- Intercalando Ondas de Inimigos ---\n");

    printf("Portal Alfa: Digite o numero de inimigos (n): ");
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    
    alfa = (int *)malloc(n * sizeof(int));
    if (alfa == NULL) return 1;

    printf("Portal Alfa: Digite os %d niveis de ameaca (ordenados):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &alfa[i]);
    }

    printf("\nPortal Beta: Digite o numero de inimigos (m): ");
    if (scanf("%d", &m) != 1 || m < 0) {
        free(alfa);
        return 1;
    }
    
    beta = (int *)malloc(m * sizeof(int));
    if (beta == NULL) {
        free(alfa);
        return 1;
    }

    printf("Portal Beta: Digite os %d niveis de ameaca (ordenados):\n", m);
    for (i = 0; i < m; i++) {
        scanf("%d", &beta[i]);
    }

    int tamanho_total = n + m;
    unificado = (int *)malloc(tamanho_total * sizeof(int));
    if (unificado == NULL) {
        free(alfa);
        free(beta);
        return 1;
    }

    intercalar_vetores(alfa, n, beta, m, unificado);

    printf("\n--- Lista Unificada e Ordenada de Ameacas ---\n");
    for (i = 0; i < tamanho_total; i++) {
        printf("%d ", unificado[i]);
    }
    printf("\n");

    free(alfa);
    free(beta);
    free(unificado);

    return 0;
}