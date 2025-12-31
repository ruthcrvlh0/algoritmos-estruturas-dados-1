#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

typedef struct {
    char nome[50];
    int custo_mana;
} Feitico;

typedef struct no {
    Feitico dado;
    struct no *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

void menu();
void inicializar_pilha(Pilha *p);
void push(Pilha *p, Feitico f); 
void liberar_pilha(Pilha *p);

/**
 * @brief Adiciona um novo feitiço ao topo da pilha (operação PUSH).
 * Simula a inserção no início de uma lista encadeada.
 * @param p Ponteiro para a Pilha.
 * @param f Dados do Feitiço a ser inserido.
 */
void push(Pilha *p, Feitico f) {
    No *novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("[ERRO] Falha na alocacao de memoria para o feitiço.\n");
        return;
    }

    novo_no->dado = f;
    novo_no->prox = p->topo; 
    p->topo = novo_no;
    
    printf("[LOG] Comando '%s' (Custo: %d) adicionado ao TOPO da pilha.\n", f.nome, f.custo_mana);
}

int main() {
    Pilha comandos_arcanista;
    inicializar_pilha(&comandos_arcanista);
    int op;
    Feitico novo_feitico;

    do {
        menu();
        if (scanf("%d", &op) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(op) {
            case 1:
                printf("\n--- Novo Comando de Feitiço ---\n");
                printf("Nome do Feitiço: ");
                scanf("%49s", novo_feitico.nome);
                printf("Custo de Mana: ");
                scanf("%d", &novo_feitico.custo_mana);
                push(&comandos_arcanista, novo_feitico);
                break;
                
            case 2:
                printf("\nFinalizando a sequencia de comandos. Pilha de comandos preparada.\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(op != 2);

    liberar_pilha(&comandos_arcanista);

    return 0;
}

void menu() {
    printf("\n--- Pilha de Comandos do Arcanista ---\n");
    printf("1: Adicionar um novo feitiço (PUSH)\n");
    printf("2: Finalizar a sequencia de comandos e sair\n");
    printf("Escolha uma opcao: ");
}

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}

void liberar_pilha(Pilha *p) {
    No *atual = p->topo;
    No *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    p->topo = NULL;
    printf("[LOG] Memoria da pilha de comandos liberada.\n");
}