#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void criarFila(Fila *f);
void entrar(Fila *f, int id, char *nick);
void mostrar(Fila *f);
Jogador remover(Fila *f); 

void criarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
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

    if (f->inicio == NULL) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    f->fim = novo;
    printf(">> Jogador %s entrou na fila.\n", nick);
}

void mostrar(Fila *f) {
    if (f->inicio == NULL) {
        printf("\n>> Fila vazia.\n");
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
    if (f->inicio == NULL) {
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
        printf("4. Sair\n");
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
                    printf("\n>> SUCESSO! O jogador %s (ID: %d) saiu da fila e foi para a partida.\n", 
                           jRemovido.nickname, jRemovido.id);
                }
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}