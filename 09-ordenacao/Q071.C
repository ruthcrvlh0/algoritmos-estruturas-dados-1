#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int nivel_ameaca;
} Nave;

/**
 * @brief Intercala dois subvetores ordenados (arr[p...q] e arr[q+1...r]) em um vetor temporário,
 * mantendo a ordem crescente do nivel_ameaca.
 */
void merge(Nave arr[], int p, int q, int r) {
    int i, j, k;
    int n1 = q - p + 1; 
    int n2 = r - q;    

    Nave *L = (Nave *)malloc(n1 * sizeof(Nave));
    Nave *R = (Nave *)malloc(n2 * sizeof(Nave));

    if (L == NULL || R == NULL) {
        if (L) free(L);
        if (R) free(R);
        return; 
    }

    for (i = 0; i < n1; i++) {
        L[i] = arr[p + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[q + 1 + j];
    }

    i = 0; 
    j = 0; a
    k = p; 

    while (i < n1 && j < n2) {
        if (L[i].nivel_ameaca <= R[j].nivel_ameaca) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

/**
 * @brief Função principal do Merge Sort.
 * @param arr O vetor de naves a ser ordenado.
 * @param p O índice de início do segmento atual.
 * @param r O índice de fim do segmento atual.
 */
void mergeSort(Nave arr[], int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

int main() {
    int N;
    int i;
    Nave *frota = NULL;

    printf("--- Modulo de Priorizacao de Alvos (Merge Sort) ---\n");

    printf("Digite o numero de naves inimigas (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    frota = (Nave *)malloc(N * sizeof(Nave));
    if (frota == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite o ID e o Nivel de Ameaca para cada uma das %d naves:\n", N);
    for (i = 0; i < N; i++) {
        printf("Nave %d (ID Ameaca): ", i + 1);
        scanf("%d %d", &frota[i].id, &frota[i].nivel_ameaca);
    }

    mergeSort(frota, 0, N - 1);

    printf("\n--- Sequencia de Alvos por Prioridade (Menor Ameaca Primeiro) ---\n");
    for (i = 0; i < N; i++) {
        printf("%d ", frota[i].id);
    }
    printf("\n");

    free(frota);
    frota = NULL;

    return 0;
}