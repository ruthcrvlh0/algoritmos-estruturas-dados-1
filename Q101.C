#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void mostrar_pilha(Pilha *p); 
void liberar_pilha(Pilha *p);

/**
 * @brief Exibe todos os feitiços na pilha, do topo para a base.
 * @param p Ponteiro para a Pilha.
 */
void mostrar_pilha(Pilha *p) {
    if (p->topo == NULL) {
        printf("\n[AVISO] A pilha de comandos esta vazia.\n");
        return;
    }

    printf("\n--- Pilha de Comandos do Arcanista (Ordem LIFO) ---\n");
    No *atual = p->topo;
    
    printf("        <-- TOPO DA PILHA (Proximo a executar)\n");
    
    while (atual != NULL) {
        printf("Comando: %s | Mana: %d\n", atual->dado.nome, atual->dado.custo_mana);
        atual = atual->prox;
    }
    
    printf("        <-- BASE DA PILHA (Ultimo a executar)\n");
    printf("--------------------------------------------------\n");
}

void push(Pilha *p, Feitico f) {
    No *novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("[ERRO] Falha na alocacao de memoria.\n");
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
                mostrar_pilha(&comandos_arcanista);
                break;
                
            case 3:
                printf("\nFinalizando a sequencia de comandos. Pilha de comandos preparada.\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(op != 3);

    liberar_pilha(&comandos_arcanista);
    return 0;
}

void menu() {
    printf("\n--- Pilha de Comandos do Arcanista ---\n");
    printf("1: Adicionar um novo feitiço (PUSH)\n");
    printf("2: Mostrar Pilha de Comandos\n"); 
    printf("3: Finalizar e sair\n");         
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
}