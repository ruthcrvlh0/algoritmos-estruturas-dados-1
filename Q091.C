#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---
typedef struct {
    int id;
    char descricao[100];
} Etapa;

typedef struct No {
    Etapa etapa;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} Lista;

// --- PROTÓTIPOS ---
void menu();
void inserir_fim(Lista *lista, Etapa e);
void mostrar(Lista lista);
void deletar_antes(Lista *lista, int id_ref);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    Lista lista;
    lista.inicio = NULL;
    int op, id_ref;
    Etapa e;

    do {
        menu();
        if (scanf("%d", &op) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n'); 
            continue;
        }
        getchar(); 

        switch(op) {
            case 1:
                printf("\nDigite o ID da etapa: ");
                scanf("%d", &e.id);
                getchar(); 
                printf("Digite a descricao da etapa: ");
                fgets(e.descricao, 100, stdin);
                e.descricao[strcspn(e.descricao, "\n")] = 0; 
                inserir_fim(&lista, e);
                break;
            case 2:
                mostrar(lista);
                break;
            case 3:
                printf("\nInforme o ID da etapa de referencia (a que permanece): ");
                if (scanf("%d", &id_ref) == 1) {
                    deletar_antes(&lista, id_ref);
                } else {
                    printf("\nID de referencia invalido.\n");
                    while (getchar() != '\n');
                }
                break;
            case 4:
                printf("\nFinalizando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(op != 4);

    No *atual = lista.inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---
void menu() {
    printf("\n--- Gerenciador de Etapas de Missao ---\n");
    printf("1 - Inserir etapa no fim\n");
    printf("2 - Mostrar etapas\n");
    printf("3 - Deletar etapa ANTES de um ID\n");
    printf("4 - Sair\n");
    printf("Escolha uma opcao: ");
}

void inserir_fim(Lista *lista, Etapa e) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("[ERRO] Erro de alocacao de memoria!\n");
        return;
    }
    novo->etapa = e;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *pi = lista->inicio;
        while (pi->prox != NULL) {
            pi = pi->prox;
        }
        pi->prox = novo;
    }
    printf("[LOG] Etapa '%s' inserida com sucesso!\n", e.descricao);
}

void mostrar(Lista lista) {
    printf("\n--- Diário de Missao ---\n");
    if (lista.inicio == NULL) {
        printf("Nenhuma etapa registrada.\n");
        return;
    }
    No *pi = lista.inicio;
    while (pi != NULL) {
        printf("ID: %d - Descricao: %s\n", pi->etapa.id, pi->etapa.descricao);
        pi = pi->prox;
    }
    printf("------------------------\n");
}

void deletar_antes(Lista *lista, int id_ref) {
    if (lista->inicio == NULL) {
        printf("[ERRO] Lista vazia. Nao ha etapas para deletar.\n");
        return;
    }

    No *anterior_ao_anterior = NULL; 
    No *anterior = NULL;             
    No *atual = lista->inicio;       
    while (atual != NULL && atual->etapa.id != id_ref) {
        anterior_ao_anterior = anterior;
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("[ERRO] Etapa de referencia com ID %d nao encontrada.\n", id_ref);
        return;
    }
    
    if (anterior == NULL) {
        printf("[AVISO] A etapa de referencia '%s' (ID %d) e a primeira. Nao ha etapa ANTERIOR para deletar.\n", 
               atual->etapa.descricao, id_ref);
        return;
    }

    if (anterior_ao_anterior == NULL) {
        printf("[SUCESSO] Etapa '%s' (ID %d) deletada. Era a primeira da lista.\n", 
               anterior->etapa.descricao, anterior->etapa.id);
        lista->inicio = atual; 
    }
    else {
        anterior_ao_anterior->prox = atual; 
        printf("[SUCESSO] Etapa '%s' (ID %d) deletada. Apos atalho, a etapa %d foi removida.\n", 
               anterior->etapa.descricao, anterior->etapa.id, id_ref);
    }
    
    free(anterior);
}