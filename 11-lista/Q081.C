#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
} Movimento;

typedef struct no {
    Movimento dado; 
    struct no *proximo;
} No;

typedef struct {
    No *inicio; 
} Lista;

// --- Implementação da Inserção no Início (Push) ---

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
 * @brief Insere um novo movimento no início do combo.
 * @param lista Ponteiro para a lista encadeada (o combo).
 * @param novo_movimento O struct Movimento a ser inserido.
 */
void inserir_no_inicio(Lista *lista, Movimento novo_movimento) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return;
    }

    novo_no->dado = novo_movimento;

    novo_no->proximo = lista->inicio;

    lista->inicio = novo_no;

    printf("\n[LOG] Movimento '%s' (ID %d) inserido como o MAIS RECENTE.\n", 
           novo_movimento.nome, novo_movimento.id);
}

// --- Funções Auxiliares de Limpeza ---

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
    Lista *log_combo = inicializar_lista();
    int opcao;
    Movimento novo_movimento;

    do {
        printf("\n--- Log de Combo ---\n");
        printf("1: Inserir novo movimento no inicio do combo.\n");
        printf("2: Sair.\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\nDigite o ID do movimento: ");
                scanf("%d", &novo_movimento.id);
                printf("Digite o nome do movimento (sem espacos): ");
                scanf("%s", novo_movimento.nome);
                
                inserir_no_inicio(log_combo, novo_movimento);
                break;
                
            case 2:
                printf("\nEncerrando o sistema de log de combo.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1 ou 2.\n");
                break;
        }
    } while (opcao != 2);

    liberar_lista(log_combo);

    return 0;
}