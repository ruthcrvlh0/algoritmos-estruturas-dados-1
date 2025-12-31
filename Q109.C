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
void mostrar(Fila *f); /

void criarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void entrar(Fila *f, int id, char *nick) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
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
    printf(">> Jogador %s entrou na fila com sucesso!\n", nick);
}

void mostrar(Fila *f) {
    if (f->inicio == NULL) {
        printf("\n>> A fila de matchmaking esta vazia.\n");
        return;
    }

    No *aux = f->inicio;

    printf("\n--- Fila de Matchmaking Atual ---\n");
    printf("POS | ID   | NICKNAME\n");
    printf("-------------------------------\n");

    int posicao = 1;

    while (aux != NULL) {
        printf("#%d  | %-4d | %s\n", posicao, aux->dados.id, aux->dados.nickname);
        
        aux = aux->proximo;
        posicao++;
    }
    printf("-------------------------------\n");
}


int main() {
    Fila filaMatchmaking;
    criarFila(&filaMatchmaking);

    int opcao, id;
    char nickname[50];

    do {
        printf("\n=== SISTEMA DE MATCHMAKING (MOBA) ===\n");
        printf("1. Adicionar Jogador na Fila\n");
        printf("2. Mostrar Fila\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o ID do jogador: ");
                scanf("%d", &id);
                printf("Digite o Nickname: ");
                scanf(" %[^\n]", nickname); 
                entrar(&filaMatchmaking, id, nickname);
                break;

            case 2:
                mostrar(&filaMatchmaking);
                break;

            case 3:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 3);
    
    return 0;
}