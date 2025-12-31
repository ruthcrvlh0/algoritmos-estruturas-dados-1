#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estruturas de Dados ---

typedef struct {
    int id;
    char nickname[50];
} Jogador;

typedef struct no {
    Jogador dados;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

// --- Protótipos ---
void criarFila(Fila *f);
void entrar(Fila *f, int id, char *nick);
void mostrar(Fila *f);
Jogador remover(Fila *f);
int estaVazia(Fila *f); 

void criarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}


int estaVazia(Fila *f) {
    if (f->inicio == NULL) {
        return 1; 
    } else {
        return 0; 
    }
}

void entrar(Fila *f, int id, char *nick) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }
    novo->dados.id = id;
    strcpy(novo->dados.nickname, nick);
    novo->proximo = NULL;

    if (estaVazia(f)) { 
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    f->fim = novo;
    printf(">> Jogador %s entrou na fila.\n", nick);
}

void mostrar(Fila *f) {
    if (estaVazia(f)) { 
        printf("\n>> A fila de matchmaking esta vazia.\n");
        return;
    }
    No *aux = f->inicio;
    printf("\n--- Fila Atual ---\n");
    while (aux != NULL) {
        printf("ID: %d | Nick: %s\n", aux->dados.id, aux->dados.nickname);
        aux = aux->proximo;
    }
    printf("------------------\n");
}

Jogador remover(Fila *f) {
    if (estaVazia(f)) {
        printf("\n>> Erro: A fila esta vazia! Ninguem para remover.\n");
        Jogador jVazio;
        jVazio.id = -1; 
        return jVazio;
    }

    No *noRemover = f->inicio;
    Jogador dadosJogador = noRemover->dados;

    f->inicio = f->inicio->proximo;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(noRemover);
    return dadosJogador;
}

int main() {
    Fila filaMatchmaking;
    criarFila(&filaMatchmaking);

    int opcao, id;
    char nickname[50];
    Jogador jRemovido;

    do {
        printf("\n=== SISTEMA DE MATCHMAKING ===\n");
        printf("1. Adicionar Jogador\n");
        printf("2. Mostrar Fila\n");
        printf("3. Remover Jogador (Iniciar Partida)\n");
        printf("4. Verificar se a Fila esta Vazia\n"); 
        printf("5. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("ID: "); scanf("%d", &id);
                printf("Nick: "); scanf(" %[^\n]", nickname);
                entrar(&filaMatchmaking, id, nickname);
                break;
            case 2:
                mostrar(&filaMatchmaking);
                break;
            case 3:
                jRemovido = remover(&filaMatchmaking);
                if (jRemovido.id != -1) {
                    printf("\n>> SUCESSO! Jogador %s saiu da fila.\n", jRemovido.nickname);
                }
                break;
            case 4:
                if (estaVazia(&filaMatchmaking)) {
                    printf("\n>> STATUS: SIM, a fila esta vazia.\n");
                } else {
                    printf("\n>> STATUS: NAO, a fila contem jogadores esperando.\n");
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}