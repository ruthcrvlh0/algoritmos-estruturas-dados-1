#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Simula a fase de Partição, reorganizando o vetor em torno do pivô (último elemento).
 * @param n O tamanho do vetor.
 * @param v O vetor de níveis de poder (entrada e saída).
 */
void particao(int n, int v[]) {
    if (n <= 1) {
        return;
    }

    int pivo = v[n - 1]; 
    
    int *s = (int *)malloc(n * sizeof(int));
    if (s == NULL) {
        perror("Erro ao alocar memoria para o vetor secundario");
        return;
    }

    int i;
    int indice_menores_ou_iguais = 0;
    int indice_maiores = n - 1;      


    for (i = 0; i < n - 1; i++) {
        if (v[i] <= pivo) {
            s[indice_menores_ou_iguais] = v[i];
            indice_menores_ou_iguais++;
        } else {
            s[indice_maiores] = v[i];
            indice_maiores--;
        }
    }

    s[indice_menores_ou_iguais] = pivo;

    for (i = 0; i < n; i++) {
        v[i] = s[i];
    }
    
    free(s);
}

int main() {
    int N;
    int i;
    int *v = NULL;

    printf("--- Triagem Rapida de Itens (Particao do Quick Sort) ---\n");

    printf("Digite a quantidade de itens no bau (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. Encerrando.\n");
        return 1;
    }

    v = (int *)malloc(N * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d niveis de poder separados por espaco: ", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }

    printf("\nVetor Original (Pivo: %d):\n", v[N - 1]);
    for (i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    particao(N, v);

    printf("\nItens Reorganizados (<= Pivo | Pivo | > Pivo):\n");
    for (i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    free(v);
    v = NULL;

    return 0;
}