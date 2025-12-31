#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int mat;
    char nome[100];
} Estudante;

typedef struct No {
    Estudante dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} Lista;

void menu() {
    printf("\n======== Gerenciador de Party =========\n");
    printf("1 - Adicionar jogador no inicio da party\n");
    printf("2 - Adicionar jogador no fim da party\n");
    printf("5 - Mostrar membros da party\n");
    printf("7 - Remover primeiro jogador da party\n");
    printf("8 - Remover ultimo jogador da party\n");
    printf("9 - Sair\n");
    printf("=======================================\n");
}

void ler(Estudante *e) {
    printf("Digite a matricula: ");
    scanf("%d", &e->mat);
    printf("Digite o nome: ");
    scanf(" %[^\n]s", e->nome); 
}

void inserir_inicio(Lista *plista, Estudante dado) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) { perror("Erro de alocação"); return; }
    novo->dado = dado;
    novo->prox = plista->inicio;
    plista->inicio = novo;
    printf("[LOG] %s (ID %d) inserido no início.\n", dado.nome, dado.mat);
}

void inserir_fim(Lista *plista, Estudante dado) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) { perror("Erro de alocação"); return; }
    novo->dado = dado;
    novo->prox = NULL;
    
    if (plista->inicio == NULL) { 
        plista->inicio = novo;
    } else {
        No *pi;
        for (pi = plista->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
    printf("[LOG] %s (ID %d) inserido no fim.\n", dado.nome, dado.mat);
}

void mostrar(Lista lista) {
    if (lista.inicio == NULL) {
        printf("A party esta vazia!\n");
        return;
    }
    No *pi;
    printf("\n--- Membros da Party ---\n");
    for (pi = lista.inicio; pi != NULL; pi = pi->prox) {
        printf("Matricula: %d | Nome: %s\n", pi->dado.mat, pi->dado.nome);
    }
    printf("------------------------\n");
}

void deletar_inicio(Lista *plista) {
    if (plista->inicio == NULL) {
        printf("A lista ja esta vazia! Nada a remover.\n");
    } else {
        No *pi = plista->inicio;
        printf("[LOG] Removido o jogador %s (ID %d) do início.\n", pi->dado.nome, pi->dado.mat);
        plista->inicio = pi->prox;
        free(pi);
    }
}

void deletar_fim(Lista *plista) {
    // ====================================
    // INÍCIO DA IMPLEMENTAÇÃO DO CÓDIGO
    // ====================================
    
    // Caso 1: Lista Vazia
    if (plista->inicio == NULL) {
        printf("[ERRO] A Party esta vazia. Nao ha ninguem para remover do fim.\n");
        return;
    }

    No *atual = plista->inicio;
    No *anterior = NULL;

    // Caso 2: Apenas um Jogador
    if (atual->prox == NULL) {
        printf("[LOG] Removido o unico jogador %s (ID %d). Party agora esta vazia.\n", 
               atual->dado.nome, atual->dado.mat);
        free(atual);
        plista->inicio = NULL; 
        return;
    }

    // Caso 3: Vários Jogadores
    while (atual->prox != NULL) {
        anterior = atual; // 'anterior' fica um passo atrás
        atual = atual->prox; // 'atual' avança
    }
    
    printf("[LOG] Removido o ultimo jogador %s (ID %d).\n", 
           atual->dado.nome, atual->dado.mat);

    anterior->prox = NULL;

    free(atual);
    
    // ====================================
    // FIM DA IMPLEMENTAÇÃO DO CÓDIGO
    // ====================================
}

int main() {
    Lista lista;
    lista.inicio = NULL;
    int op;

    do {
        menu();
        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida. Por favor, digite um numero.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch(op) {
            case 1: {
                Estudante e;
                ler(&e);
                inserir_inicio(&lista, e);
                break;
            }
            case 2: {
                Estudante e;
                ler(&e);
                inserir_fim(&lista, e);
                break;
            }
            case 5:
                mostrar(lista);
                break;
            case 7:
                deletar_inicio(&lista);
                break;
            case 8:
                deletar_fim(&lista);
                break;
            case 9:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (op != 9);
    
    while(lista.inicio != NULL) {
        deletar_inicio(&lista);
    }
    
    return 0;
}