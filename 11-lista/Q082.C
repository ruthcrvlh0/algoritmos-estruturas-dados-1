#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
} Aventureiro;

typedef struct no {
    Aventureiro dado;
    struct no *proximo;
} No;

typedef struct {
    No *inicio; 
} Lista;

// --- Funções de Gerenciamento da Lista ---

/**
 * @brief Inicializa a lista encadeada.
 * @return Um ponteiro para a nova Lista inicializada.
 */
Lista* inicializar_lista() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        perror("Erro ao alocar memoria para a lista");
        exit(EXIT_FAILURE);
    }
    nova_lista->inicio = NULL;
    return nova_lista;
}

/**
 * @brief Adiciona um novo aventureiro no INÍCIO da lista.
 * O novo aventureiro se torna o líder temporário.
 * @param lista Ponteiro para a lista encadeada (o grupo).
 * @param novo_aventureiro O struct Aventureiro a ser inserido.
 */
void adicionar_aventureiro(Lista *lista, Aventureiro novo_aventureiro) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return;
    }

    novo_no->dado = novo_aventureiro;
    novo_no->proximo = lista->inicio;
    lista->inicio = novo_no;

    printf("\n[LOG] Aventureiro '%s' (ID %d) adicionado como LÍDER.\n", 
           novo_aventureiro.nome, novo_aventureiro.id);
}

/**
 * @brief Exibe a lista completa dos aventureiros na ordem do grupo.
 * @param lista Ponteiro para a lista encadeada (o grupo).
 */
void mostrar_grupo(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nO grupo esta vazio! Nao ha aventureiros.\n");
        return;
    }

    No *atual = lista->inicio;
    int posicao = 1;

    printf("\n--- Grupo de Aventureiros ---\n");
    while (atual != NULL) {
        printf("Posicao %d: ID %d | Nome: %s", 
               posicao, atual->dado.id, atual->dado.nome);
        
        if (posicao == 1) {
            printf(" (LÍDER ATUAL)");
        }
        printf("\n");
        
        atual = atual->proximo;
        posicao++;
    }
    printf("-----------------------------\n");
}

/**
 * @brief Libera toda a memória alocada para a lista.
 * @param lista Ponteiro para a lista encadeada.
 */
void liberar_lista(Lista *lista) {
    No *atual = lista->inicio;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

// --- Programa Principal (Menu) ---

int main() {
    Lista *grupo_aventureiros = inicializar_lista();
    int opcao;
    Aventureiro novo_membro;

    do {
        printf("\n--- Gerenciador de Grupo ---\n");
        printf("1: Adicionar Aventureiro (Novo Lider)\n");
        printf("2: Mostrar Grupo\n");
        printf("3: Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\nDigite o ID do aventureiro (inteiro): ");
                scanf("%d", &novo_membro.id);
                printf("Digite o nome do aventureiro (sem espacos): ");
                scanf("%s", novo_membro.nome);
                
                adicionar_aventureiro(grupo_aventureiros, novo_membro);
                break;
                
            case 2:
                mostrar_grupo(grupo_aventureiros);
                break;
                
            case 3:
                printf("\nEncerrando o gerenciador de grupo.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1, 2 ou 3.\n");
                break;
        }
    } while (opcao != 3);

    liberar_lista(grupo_aventureiros);
    return 0;
}