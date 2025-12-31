#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

struct Unidade {
    int x;
    int y;
};

int main() {
    int n;
    int i, j;
    float raio_explosao;
    int duplas_proximas = 0;
    struct Unidade *unidades = NULL;

    printf("--- Analise de Agrupamento de Inimigos ---\n");

    printf("Digite o numero de unidades inimigas (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero de unidades invalido. Encerrando.\n");
        return 1;
    }

    unidades = (struct Unidade *)malloc(n * sizeof(struct Unidade));
    if (unidades == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    printf("\n--- Cadastro das Coordenadas ---\n");
    for (i = 0; i < n; i++) {
        printf("Unidade %d (x y): ", i + 1);
        scanf("%d %d", &unidades[i].x, &unidades[i].y);
    }

    printf("\nDigite o raio de explosao (float): ");
    scanf("%f", &raio_explosao);

    printf("\n--- Calculando Distancias (Complexidade O(n^2)) ---\n");

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            float dx = (float)unidades[j].x - unidades[i].x;
            float dy = (float)unidades[j].y - unidades[i].y;
            float distancia;
            distancia = sqrt(pow(dx, 2) + pow(dy, 2));

            if (distancia <= raio_explosao) {
                duplas_proximas++;
                printf("Dupla proxima encontrada: (%d, %d) e (%d, %d). Distancia: %.2f\n",
                       unidades[i].x, unidades[i].y, unidades[j].x, unidades[j].y, distancia);
            }
        }
    }

    printf("\n--- Resultado Final ---\n");
    printf("Total de duplas de inimigos dentro do raio de explosao: %d\n", duplas_proximas);

    free(unidades);
    unidades = NULL;

    return 0;
}