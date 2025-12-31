#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = arr[i]; 
        j = i - 1;      
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = chave;
    }
}

int main() {
    int n;
    int i;
    int *fragmentos = NULL;

    printf("--- Ritual de Encantamento: Organizacao de Fragmentos ---\n");

    printf("Digite a quantidade de Fragmentos de Alma (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    fragmentos = (int *)malloc(n * sizeof(int));
    if (fragmentos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d niveis de poder separados por espaco: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &fragmentos[i]);
    }

    insertionSort(fragmentos, n);

    printf("\nFragmentos Ordenados (Prontos para o Ritual):\n");
    for (i = 0; i < n; i++) {
        printf("%d ", fragmentos[i]);
    }
    printf("\n");

    free(fragmentos);
    fragmentos = NULL;

    return 0;
}