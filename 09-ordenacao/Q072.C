#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int posicao;
    char nome[50];
} Piloto;

/**
 * @brief Intercala dois subvetores ordenados (arr[p...q] e arr[q+1...r]) em um vetor temporário,
 * mantendo a ordem crescente da posicao.
 */
void intercala(Piloto arr[], int p, int q, int r) {
    int i, j, k;
    int n1 = q - p + 1; 
    int n2 = r - q;    
    Piloto *L = (Piloto *)malloc(n1 * sizeof(Piloto));
    Piloto *R = (Piloto *)malloc(n2 * sizeof(Piloto));

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
    j = 0; 
    k = p; 

    while (i < n1 && j < n2) {
        if (L[i].posicao <= R[j].posicao) {
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
 * @param arr O vetor de pilotos a ser ordenado.
 * @param p O índice de início do segmento atual.
 * @param r O índice de fim do segmento atual.
 */
void mergeSort(Piloto arr[], int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);
        intercala(arr, p, q, r);
    }
}

int main() {
    int N;
    int i;
    Piloto *pilotos = NULL;

    printf("--- Ordenacao do Podio (Merge Sort) ---\n");

    printf("Digite o numero total de pilotos (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    pilotos = (Piloto *)malloc(N * sizeof(Piloto));
    if (pilotos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite a Posicao e o Nome para cada um dos %d pilotos:\n", N);
    for (i = 0; i < N; i++) {
        printf("Piloto %d (Posicao Nome): ", i + 1);
        scanf("%d %s", &pilotos[i].posicao, pilotos[i].nome); 
    }

    mergeSort(pilotos, 0, N - 1);

    printf("\n--- Classificacao Final Ordenada ---\n");
    for (i = 0; i < N; i++) {
        printf("%d %s\n", pilotos[i].posicao, pilotos[i].nome);
    }

    free(pilotos);
    pilotos = NULL;

    return 0;
}