#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[50];
} Jogador;

typedef struct no {
    Jogador dado;
    struct no *proximo;
} No;

typedef struct {
    No *inicio; 
    No *fim;    
} Lista;

// --- Funções de Inicialização e Limpeza ---

/**
 * @brief Inicializa a fila.
 * @return Um ponteiro para a nova Lista inicializada.
 */
Lista* inicializar_fila() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        perror("Erro ao alocar memoria para a lista");
        exit(EXIT_FAILURE);
    }
    nova_lista->inicio = NULL;
    nova_lista->fim = NULL;
    return nova_lista;
}

/**
 * @brief Libera toda a memória alocada para a fila.
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

// --- Funções de Inserção ---

/**
 * @brief Cria e retorna um novo nó com os dados do jogador.
 */
No* criar_novo_no(Jogador jogador) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return NULL;
    }
    novo_no->dado = jogador;
    novo_no->proximo = NULL;
    return novo_no;
}

/**
 * @brief Insere um jogador no INÍCIO da fila (prioridade).
 * @param lista Ponteiro para a fila.
 * @param jogador Os dados do jogador.
 */
void inserir_no_inicio(Lista *lista, Jogador jogador) {
    No *novo_no = criar_novo_no(jogador);
    if (novo_no == NULL) return;

    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        novo_no->proximo = lista->inicio;
        lista->inicio = novo_no;
    }
    printf("\n[LOG] Jogador %s (ID %d) adicionado com PRIORIDADE.\n", jogador.nome, jogador.matricula);
}

/**
 * @brief Insere um jogador no FIM da fila (caso principal FIFO).
 * @param lista Ponteiro para a fila.
 * @param jogador Os dados do jogador.
 */
void inserir_no_fim(Lista *lista, Jogador jogador) {
    No *novo_no = criar_novo_no(jogador);
    if (novo_no == NULL) return;

    if (lista->fim == NULL) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
    }
    printf("\n[LOG] Jogador %s (ID %d) adicionado ao FINAL da fila.\n", jogador.nome, jogador.matricula);
}

// --- Função de Exibição ---

/**
 * @brief Exibe a fila completa dos jogadores na ordem correta (início para fim).
 * @param lista Ponteiro para a fila.
 */
void mostrar_fila(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nA fila de batalha esta vazia!\n");
        return;
    }

    No *atual = lista->inicio;
    int posicao = 1;

    printf("\n--- Fila de Batalha (Ordem de Atendimento) ---\n");
    while (atual != NULL) {
        printf(" %dº na Fila: ID %d | Nome: %s\n", 
               posicao, atual->dado.matricula, atual->dado.nome);
        
        atual = atual->proximo;
        posicao++;
    }
    printf("----------------------------------------------\n");
}

int main() {
    Lista *fila_batalha = inicializar_fila();
    int opcao;
    Jogador novo_jogador;

    do {
        printf("\n--- Gerenciador de Fila ---\n");
        printf("1 - Adicionar jogador no INICIO (Prioridade)\n");
        printf("2 - Adicionar jogador no FIM (Ordem de Chegada)\n");
        printf("3 - Mostrar fila\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        if (opcao == 1 || opcao == 2) {
            printf("\n--- Novo Jogador ---\n");
            printf("Matricula/ID: ");
            scanf("%d", &novo_jogador.matricula);
            printf("Nome (sem espacos): ");
            scanf("%s", novo_jogador.nome);
        }

        switch (opcao) {
            case 1:
                inserir_no_inicio(fila_batalha, novo_jogador);
                break;
                
            case 2:
                inserir_no_fim(fila_batalha, novo_jogador);
                break;
                
            case 3:
                mostrar_fila(fila_batalha);
                break;
                
            case 4:
                printf("\nEncerrando o gerenciador de fila.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1, 2, 3 ou 4.\n");
                break;
        }
    } while (opcao != 4);

    liberar_lista(fila_batalha);

    return 0;
}