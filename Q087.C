#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
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
 * @brief Adiciona um jogador ao FIM da fila (ordem de chegada).
 */
void adicionar_no_fim(Lista *lista, Jogador jogador) {
    No *novo_no = criar_novo_no(jogador);
    if (novo_no == NULL) return;

    if (lista->fim == NULL) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
    }
    printf("\n[LOG] Jogador '%s' (ID %d) entrou na fila.\n", jogador.nome, jogador.id);
}


/**
 * @brief Remove o primeiro jogador da fila para iniciar a partida.
 * @return 1 se a remoção foi bem-sucedida, 0 caso contrário.
 */
int iniciar_partida(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\n[ERRO] Nao ha jogadores na fila. Partida nao pode ser iniciada.\n");
        return 0;
    }

    No *no_removido = lista->inicio;
    Jogador jogador_removido = no_removido->dado;

    lista->inicio = no_removido->proximo;

    if (lista->inicio == NULL) {
        lista->fim = NULL; 
    }

    free(no_removido);

    printf("\n[SUCESSO] Partida iniciada para o Jogador: ID %d | Nome: %s\n", 
           jogador_removido.id, jogador_removido.nome);
    return 1;
}


/**
 * @brief Exibe a fila completa dos jogadores na ordem correta.
 */
void mostrar_fila(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nA fila de matchmaking esta vazia!\n");
        return;
    }

    No *atual = lista->inicio;
    int posicao = 1;

    printf("\n--- Fila de Matchmaking (Primeiro a ser chamado) ---\n");
    while (atual != NULL) {
        printf(" %dº na Fila: ID %d | Nome: %s\n", 
               posicao, atual->dado.id, atual->dado.nome);
        
        atual = atual->proximo;
        posicao++;
    }
    printf("----------------------------------------------------\n");
}

int main() {
    Lista *fila = inicializar_fila();
    int opcao;
    Jogador novo_jogador;

    do {
        printf("\n--- Gerenciador de Fila de Matchmaking ---\n");
        printf("1: Adicionar jogador ao fim da fila (Entrar na fila)\n");
        printf("2: Iniciar partida (Deletar o primeiro)\n");
        printf("3: Mostrar fila de espera\n");
        printf("4: Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\n--- Novo Jogador ---\n");
                printf("ID do Jogador: ");
                scanf("%d", &novo_jogador.id);
                printf("Nome (sem espacos): ");
                scanf("%s", novo_jogador.nome);
                
                adicionar_no_fim(fila, novo_jogador);
                break;
                
            case 2:
                iniciar_partida(fila);
                break;
                
            case 3:
                mostrar_fila(fila);
                break;
                
            case 4:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1, 2, 3 ou 4.\n");
                break;
        }
    } while (opcao != 4);

    liberar_lista(fila);
    
    return 0;
}