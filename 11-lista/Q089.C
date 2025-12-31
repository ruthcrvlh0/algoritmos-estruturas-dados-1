#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição das Estruturas ---
typedef struct {
    int id;
    char nome[50];
} Heroi;

typedef struct no {
    Heroi heroi;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
} Lista;

// --- Protótipos das Funções ---
void inicializar_lista(Lista *lista);
void adicionar_heroi(Lista *lista, Heroi h);
void dispensar_heroi(Lista *lista, int id);
void mostrar_guilda(Lista *lista);
void menu();

// --- Função Principal ---
int main() {
    Lista guilda;
    inicializar_lista(&guilda);
    int opcao, id_heroi;
    Heroi novo_heroi;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida. Por favor, digite um numero.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch(opcao) {
            case 1:
                printf("\nDigite o ID do novo heroi: ");
                scanf("%d", &novo_heroi.id);
                printf("Digite o nome do novo heroi: ");
                scanf("%49s", novo_heroi.nome);
                adicionar_heroi(&guilda, novo_heroi);
                break;
            case 2:
                mostrar_guilda(&guilda);
                break;
            case 3:
                printf("\nDigite o ID do heroi a ser dispensado: ");
                if (scanf("%d", &id_heroi) == 1) {
                    dispensar_heroi(&guilda, id_heroi);
                    printf("\n--- Roster da Guilda Atualizado ---\n");
                    mostrar_guilda(&guilda);
                } else {
                    printf("\nID invalido!\n");
                    while (getchar() != '\n');
                }
                break;
            case 4:
                printf("\nSaindo do gerenciador da guilda...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 4);

    while(guilda.inicio != NULL) {
        No *temp = guilda.inicio;
        guilda.inicio = guilda.inicio->prox;
        free(temp);
    }

    return 0;
}

// --- Implementação das Funções Auxiliares ---
void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
}

void adicionar_heroi(Lista *lista, Heroi h) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo) {
        novo->heroi = h;
        novo->prox = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = novo;
        } else {
            No *aux = lista->inicio;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
        printf("[LOG] Heroi %s (ID %d) adicionado.\n", h.nome, h.id);
    } else {
        printf("[ERRO] Erro de alocacao de memoria!\n");
    }
}

void mostrar_guilda(Lista *lista) {
    printf("\n--- Roster da Guilda ---\n");
    if (lista->inicio == NULL) {
        printf("A guilda esta vazia.\n");
    } else {
        No *aux = lista->inicio;
        while (aux != NULL) {
            printf("ID: %d, Nome: %s\n", aux->heroi.id, aux->heroi.nome);
            aux = aux->prox;
        }
    }
    printf("------------------------\n");
}

void menu() {
    printf("\nGerenciador de Guilda:\n");
    printf("1. Adicionar Heroi\n");
    printf("2. Mostrar Guilda\n");
    printf("3. Dispensar Heroi por ID\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para deletar um nó baseado no ID do herói.
void dispensar_heroi(Lista *lista, int id) {
    // ====================================
    // INÍCIO DA IMPLEMENTAÇÃO DO CÓDIGO
    // ====================================
    
    // Ponteiros para busca e manipulação
    No *atual = lista->inicio;
    No *anterior = NULL;

    // 1. Caso: Lista Vazia
    if (lista->inicio == NULL) {
        printf("[ERRO] A guilda esta vazia. Nao ha herois para dispensar.\n");
        return;
    }

    // Procura o herói na lista. O loop para quando:
    // a) Encontra o herói (atual->heroi.id == id)
    // b) Chega ao fim da lista (atual == NULL)
    while (atual != NULL && atual->heroi.id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    // 4. Caso: ID não encontrado
    if (atual == NULL) {
        printf("[ERRO] Heroi com ID %d nao encontrado na guilda.\n", id);
        return;
    }

    // Neste ponto, 'atual' é o nó a ser removido.
    
    // 2. Caso: Remoção do Primeiro Herói (anterior é NULL)
    if (anterior == NULL) {
        // O novo início é o nó que vinha depois do atual
        lista->inicio = atual->prox; 
        printf("[LOG] Heroi %s (ID %d) dispensado do INÍCIO da lista.\n", atual->heroi.nome, atual->heroi.id);
    } 
    // 3. Caso: Remoção no Meio ou no Fim (anterior não é NULL)
    else {
        // O nó anterior agora aponta para o nó que vinha depois do 'atual', pulando o 'atual'
        anterior->prox = atual->prox; 
        printf("[LOG] Heroi %s (ID %d) dispensado da guilda.\n", atual->heroi.nome, atual->heroi.id);
    }

    free(atual);
    
    // ====================================
    // FIM DA IMPLEMENTAÇÃO DO CÓDIGO
    // ====================================
}