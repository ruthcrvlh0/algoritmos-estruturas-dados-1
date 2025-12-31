#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nickname[50];
    int reputacao;
} Jogador;

int busca_binaria(const Jogador *jogadores, int n, int id_busca) {
    int inicio = 0;
    int fim = n - 1;
    
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2; 
        
        if (jogadores[meio].id == id_busca) {
            return meio; 
        } else if (jogadores[meio].id < id_busca) {
            inicio = meio + 1; 
        } else {
            fim = meio - 1; 
        }
    }
    return -1; 
}

int main() {
    int n, i;
    int opcao;
    int id_busca;
    int indice_encontrado;
    Jogador *jogadores = NULL;

    printf("--- Ferramenta GM: Gestao de Reputacao ---\n");
    
    // 1. Leitura do número de jogadores
    printf("Digite o numero de jogadores a cadastrar (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero de jogadores invalido. Encerrando.\n");
        return 1;
    }

    // Alocação dinâmica de memória
    jogadores = (Jogador *)malloc(n * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    // 2. Leitura dos dados dos N jogadores (IDs devem ser inseridos em ordem crescente)
    printf("\n--- Cadastro de Jogadores (IDs em ordem crescente) ---\n");
    for (i = 0; i < n; i++) {
        printf("\nJogador %d:\n", i + 1);
        printf(" ID: ");
        scanf("%d", &jogadores[i].id);
        
        printf(" Nickname: ");
        scanf("%s", jogadores[i].nickname);
        
        printf(" Reputacao Inicial: ");
        scanf("%d", &jogadores[i].reputacao);
    }

    // 3. Loop do menu
    do {
        printf("\n=========================================\n");
        printf("Menu:\n");
        printf("1 - Adicionar Reputacao (+100)\n");
        printf("2 - Sair\n");
        printf("Escolha a opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); 
            opcao = 0;
            continue;
        }

        if (opcao == 1) {
            printf("Digite o ID do jogador para conceder recompensa: ");
            if (scanf("%d", &id_busca) != 1) {
                while(getchar() != '\n'); 
                continue;
            }

            indice_encontrado = busca_binaria(jogadores, n, id_busca);

            if (indice_encontrado != -1) {
                jogadores[indice_encontrado].reputacao += 100;
                printf("\n[SUCESSO] Recompensa concedida!\n");
                printf("Nickname: %s, Nova Reputacao: %d\n", 
                       jogadores[indice_encontrado].nickname, 
                       jogadores[indice_encontrado].reputacao);
            } else {
                printf("\nERRO: Jogador com ID %d nao encontrado.\n", id_busca);
            }
        }

    } while (opcao != 2);

    printf("\nEncerrando a ferramenta de GM.\n");
    free(jogadores);
    jogadores = NULL;

    return 0;
}