#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortOtimizadoDecrescente(int arr[], int n) {
    int i, j;
    bool trocou; 

    for (i = 0; i < n - 1; i++) {
        trocou = false; 

        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                trocar(&arr[j], &arr[j + 1]);
                trocou = true;
            }
        }

        if (trocou == false) {
            break; 
        }
    }
}

int main() {
    int n;
    int i;
    int *pontuacoes = NULL;

    printf("--- Placar de Pontuacoes Eficiente (Bubble Sort Otimizado) ---\n");

    printf("Digite a quantidade de pontuacoes (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    pontuacoes = (int *)malloc(n * sizeof(int));
    if (pontuacoes == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite as %d pontuacoes separadas por espaco: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &pontuacoes[i]);
    }

    bubbleSortOtimizadoDecrescente(pontuacoes, n);

    printf("\nPlacar Ordenado (Maior para a Menor Pontuacao):\n");
    for (i = 0; i < n; i++) {
        printf("%d ", pontuacoes[i]);
    }
    printf("\n");

    free(pontuacoes);
    pontuacoes = NULL;

    return 0;
}