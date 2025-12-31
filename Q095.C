#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// Struct para representar o Inimigo
typedef struct {
    int id;
    char tipo[50];
} Inimigo;

// Struct para o Nó da Lista
typedef struct no {
    Inimigo dado;
    struct no *proximo;
} No;

// Struct para a Lista (Onda de Inimigos)
typedef struct {
    No *inicio;
} Lista;

// --- PROTÓTIPOS ---
void menu();
void inserir_fim(Lista *lista, Inimigo i);
void exibir_onda(Lista *lista);
void liberar_lista(Lista *lista);
Lista* criar_lista(int n); // Função foco

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---

void menu() {
    printf("\n--- Gerenciador de Ondas de Inimigos ---\n");
    printf("1. Iniciar Nova Onda (Substituir Lista)\n"); // Opção principal
    printf("2. Exibir Onda Atual\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}

void inserir_fim(Lista *lista, Inimigo i) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("[ERRO] Erro de alocacao de memoria!\n");
        return;
    }
    novo->dado = i;
    novo->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *aux = lista->inicio;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}

void exibir_onda(Lista *lista) {
    printf("\n--- Lista de Alvos Ativos ---\n");
    if (lista == NULL || lista->inicio == NULL) {
        printf("Nenhuma onda ativa.\n");
    } else {
        No *aux = lista->inicio;
        while (aux != NULL) {
            printf("ID: %d | Tipo: %s\n", aux->dado.id, aux->dado.tipo);
            aux = aux->proximo;
        }
    }
    printf("------------------------------\n");
}

/**
 * @brief Libera toda a memória alocada para os nós de uma lista.
 */
void liberar_lista(Lista *lista) {
    if (lista == NULL) return;
    No *atual = lista->inicio;
    No *temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = NULL;
}

/**
 * @brief Cria uma nova lista de inimigos com 'n' elementos lidos do usuário.
 * @param n O número de inimigos a serem lidos e inseridos.
 * @return Um ponteiro para a nova Lista encadeada.
 */
Lista* criar_lista(int n) {
    Lista *nova_onda = (Lista*)malloc(sizeof(Lista));
    if (nova_onda == NULL) exit(EXIT_FAILURE);
    nova_onda->inicio = NULL;

    printf("\n--- Criando Nova Onda com %d Inimigos ---\n", n);
    
    for (int i = 0; i < n; i++) {
        Inimigo novo_inimigo;
        
        printf("Inimigo %d:\n", i + 1);
        printf("  ID: ");
        scanf("%d", &novo_inimigo.id);
        printf("  Tipo: ");
        scanf("%49s", novo_inimigo.tipo); 

        inserir_fim(nova_onda, novo_inimigo);
    }

    printf("[LOG] Nova onda criada com sucesso.\n");
    return nova_onda;
}

int main() {
    Lista *onda_atual = (Lista*)malloc(sizeof(Lista));
    if (onda_atual == NULL) exit(EXIT_FAILURE);
    onda_atual->inicio = NULL;

    int opcao;
    int num_inimigos;
    Lista *nova_onda = NULL;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n');
            opcao = 0;
            continue;
        }

        switch(opcao) {
            case 1:
                printf("\nQuantos inimigos tera a nova onda? ");
                if (scanf("%d", &num_inimigos) < 1 || num_inimigos <= 0) {
                     printf("[ERRO] Numero de inimigos invalido.\n");
                     break;
                }
                
                liberar_lista(onda_atual);
                nova_onda = criar_lista(num_inimigos);
                onda_atual->inicio = nova_onda->inicio;
                
                free(nova_onda); 

                printf("\n[SUCESSO] Nova onda iniciada!\n");
                break;
            case 2:
                exibir_onda(onda_atual);
                break;
            case 3:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 3);

    liberar_lista(onda_atual);
    free(onda_atual);

    return 0;
}