#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    int hp;
    int ataque;
} Monstro;

/**
 * @brief Busca um monstro por ID em um vetor ordenado usando recursão.
 * @param bestiario O vetor de structs Monstro.
 * @param id_busca O ID a ser procurado.
 * @param inicio O índice inicial da sublista atual.
 * @param fim O índice final da sublista atual.
 * @return O índice do monstro no vetor ou -1 se não for encontrado.
 */
 
int busca_binaria_recursiva(const Monstro *bestiario, int id_busca, int inicio, int fim) {

    if (inicio > fim) {
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;
   
    if (bestiario[meio].id == id_busca) {
        return meio;
    }

    if (bestiario[meio].id < id_busca) {
        return busca_binaria_recursiva(bestiario, id_busca, meio + 1, fim);
    } else {
        return busca_binaria_recursiva(bestiario, id_busca, inicio, meio - 1);
    }
}

int main() {
    int N, i;
    int id_busca;
    int indice_encontrado;
    Monstro *bestiario = NULL;

    printf("--- Sistema de Busca do Bestiario (Recursivo) ---\n");

    printf("Digite o numero de monstros a catalogar (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Numero de monstros invalido. Encerrando.\n");
        return 1;
    }

    bestiario = (Monstro *)malloc(N * sizeof(Monstro));
    if (bestiario == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    printf("\n--- Cadastro dos Monstros (%d no total) ---\n", N);
    for (i = 0; i < N; i++) {
        printf("Monstro %d (ID Nome HP Ataque): ", i + 1);
        scanf("%d %s %d %d", 
              &bestiario[i].id, 
              bestiario[i].nome, 
              &bestiario[i].hp, 
              &bestiario[i].ataque);
    }


    printf("\n--- Console de Busca ---\n");
    do {
        printf("\nDigite o ID do monstro a buscar (ou 0 para sair): ");
        if (scanf("%d", &id_busca) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        if (id_busca == 0) {
            break;
        }

        indice_encontrado = busca_binaria_recursiva(bestiario, id_busca, 0, N - 1);

        if (indice_encontrado != -1) {
            Monstro m = bestiario[indice_encontrado];
            printf("Monstro Encontrado: %s (ID: %d) - HP: %d, Ataque: %d\n", 
                   m.nome, m.id, m.hp, m.ataque);
        } else {
            printf("Monstro com ID %d nao encontrado.\n", id_busca);
        }

    } while (id_busca != 0);

    printf("\nFechando Bestiario. Adeus!\n");
    free(bestiario);
    bestiario = NULL;

    return 0;
}