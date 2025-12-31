#include <stdio.h>
#include <stdlib.h>

struct Moeda {
    int posicao_x;
    int posicao_y;
    int valor;
};

int main() {
    int num_moedas;
    int total_pontos = 0;
    struct Moeda *vetor_moedas = NULL;

    printf("--- Gerenciamento de Moedas do Nivel ---\n");
    printf("Quantas moedas serao cadastradas? ");
    scanf("%d", &num_moedas);

    if (num_moedas <= 0) {
        printf("Nao ha moedas para cadastrar.\n");
        return 0;
    }

    vetor_moedas = (struct Moeda *)malloc(num_moedas * sizeof(struct Moeda));

    if (vetor_moedas == NULL) {
        printf("Erro: Falha ao alocar memoria para as moedas.\n");
        return 1;
    }

    printf("\n--- Cadastro das Moedas ---\n");
    for (int i = 0; i < num_moedas; i++) {
        printf("Moeda %d:\n", i + 1);
        printf(" Posicao X: ");
        scanf("%d", &vetor_moedas[i].posicao_x);
        printf(" Posicao Y: ");
        scanf("%d", &vetor_moedas[i].posicao_y);
        printf(" Valor: ");
        scanf("%d", &vetor_moedas[i].valor);
    }

    for (int i = 0; i < num_moedas; i++) {
        total_pontos += vetor_moedas[i].valor;
    }

    printf("\n--- Resultado Final ---\n");
    printf("Pontuacao maxima do nivel: %d\n", total_pontos);

    free(vetor_moedas);
    vetor_moedas = NULL;

    return 0;
}