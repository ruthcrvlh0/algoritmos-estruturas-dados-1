#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[100];
    char status[20]; 
} Missao;

typedef struct no {
    Missao dado;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
} Lista;


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
 * @brief Adiciona uma nova missão no FINAL do diário.
 */
void adicionar_missao(Lista *lista, Missao nova_missao) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return;
    }

    novo_no->dado = nova_missao;
    novo_no->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
    } else {
        No *atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }

    printf("\n[LOG] Missao '%s' (ID %d) adicionada ao diario.\n", nova_missao.titulo, nova_missao.id);
}

/**
 * @brief Exibe todas as missões no diário.
 */
void mostrar_missoes(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nO diario de missoes esta vazio.\n");
        return;
    }

    No *atual = lista->inicio;
    printf("\n--- Diario de Missoes Ativas ---\n");
    while (atual != NULL) {
        printf("ID: %d | Titulo: %s | Status: %s\n", 
               atual->dado.id, atual->dado.titulo, atual->dado.status);
        
        atual = atual->proximo;
    }
    printf("--------------------------------\n");
}

// Implementação da Função de Pesquisa por ID (Requisito principal)
/**
 * @brief Procura uma missão pelo ID na lista encadeada.
 * @param lista Ponteiro para a lista de missões.
 * @param id_busca O ID da missão a ser procurada.
 * @return Ponteiro para o nó da missão encontrada, ou NULL se não encontrada.
 */
No* pesquisar_missao(const Lista *lista, int id_busca) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado.id == id_busca) {
            return atual; // Missão encontrada!
        }
        atual = atual->proximo;
    }
    return NULL; 
}

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

int main() {
    Lista *quest_log = inicializar_lista();
    int opcao;
    int id_busca;
    Missao nova_missao;
    No *missao_encontrada = NULL;

    do {
        printf("\n--- Gerenciador do Diario de Missoes ---\n");
        printf("1: Adicionar Missao\n");
        printf("2: Mostrar Missoes\n");
        printf("3: Buscar Missao por ID\n");
        printf("4: Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\n--- Nova Missao ---\n");
                printf("ID (inteiro): ");
                scanf("%d", &nova_missao.id);
                printf("Titulo (sem espacos): ");
                scanf("%s", nova_missao.titulo);
                printf("Status (ex: Ativa): ");
                scanf("%s", nova_missao.status);
                
                adicionar_missao(quest_log, nova_missao);
                break;
                
            case 2:
                mostrar_missoes(quest_log);
                break;
                
            case 3:
                printf("\nDigite o ID da missao que deseja buscar: ");
                scanf("%d", &id_busca);
                
                missao_encontrada = pesquisar_missao(quest_log, id_busca);
                
                if (missao_encontrada != NULL) {
                    printf("\n--- Missao Encontrada! ---\n");
                    printf("ID: %d\n", missao_encontrada->dado.id);
                    printf("Titulo: %s\n", missao_encontrada->dado.titulo);
                    printf("Status: %s\n", missao_encontrada->dado.status);
                    printf("---------------------------\n");
                } else {
                    printf("\nMissao nao encontrada! (ID %d)\n", id_busca);
                }
                break;
                
            case 4:
                printf("\nEncerrando o diario de missoes.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1, 2, 3 ou 4.\n");
                break;
        }
    } while (opcao != 4);

    liberar_lista(quest_log);
    return 0;
}