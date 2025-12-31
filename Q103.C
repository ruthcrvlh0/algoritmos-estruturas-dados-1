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
int vazia(Pilha *p);            
void push(Pilha *p, Feitico f); 
Feitico pop(Pilha *p);
void mostrar_pilha(Pilha *p);
void liberar_pilha(Pilha *p);

/**
 * @brief Verifica se a pilha está vazia.
 * @param p Ponteiro para a Pilha.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
 */
int vazia(Pilha *p) {
    return (p->topo == NULL);
}

// ------------------------------------------------------------------
// --- FUNÇÕES REFATORADAS PARA USAR vazia() ---
// ------------------------------------------------------------------

Feitico pop(Pilha *p) {
    Feitico falha;
    strcpy(falha.nome, "NENHUM");
    falha.custo_mana = -1; 
    
    if (vazia(p)) {
        printf("\n[ERRO] A pilha de comandos esta vazia! Nao ha feitiços para lancar.\n");
        return falha;
    }

    No *no_removido = p->topo;
    Feitico lancado = no_removido->dado;

    p->topo = no_removido->prox;
    free(no_removido);
    
    return lancado;
}

void mostrar_pilha(Pilha *p) {
    if (vazia(p)) {
        printf("\n[AVISO] A pilha de comandos esta vazia.\n");
        return;
    }

    printf("\n--- Pilha de Comandos (LIFO) ---\n");
    No *atual = p->topo;
    
    printf("        <-- TOPO DA PILHA (Proximo a lancar)\n");
    while (atual != NULL) {
        printf("Comando: %s | Mana: %d\n", atual->dado.nome, atual->dado.custo_mana);
        atual = atual->prox;
    }
    printf("        <-- BASE DA PILHA (Ultimo a lancar)\n");
    printf("--------------------------------------\n");
}

// ------------------------------------------------------------------
// --- FUNÇÃO PRINCIPAL E AUXILIARES RESTANTES ---
// ------------------------------------------------------------------

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
                
            case 2: { 
                Feitico resultado = pop(&comandos_arcanista);
                if (resultado.custo_mana != -1) {
                    printf("\n[SUCESSO] Feitiço '%s' (Custo: %d) lançado com sucesso!\n", 
                           resultado.nome, resultado.custo_mana);
                }
                break;
            }
                
            case 3: 
                mostrar_pilha(&comandos_arcanista);
                break;
            
            case 4: { 
                printf("\n--- Status da Pilha de Comandos ---\n");
                if (vazia(&comandos_arcanista)) {
                    printf("Status: A pilha de comandos está VAZIA. Nenhuma ação pendente.\n");
                } else {
                    printf("Status: A pilha de comandos possui FEITIÇOS PENDENTES. Pronto para a ação!\n");
                }
                break;
            }
                
            case 5: 
                printf("\nFinalizando o sistema de comando. O Arcanista descansa.\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(op != 5);

    liberar_pilha(&comandos_arcanista);
    return 0;
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

void menu() {
    printf("\n--- Pilha de Comandos do Arcanista ---\n");
    printf("1: Adicionar um novo feitiço (PUSH)\n");
    printf("2: Lançar Próximo Feitiço (POP)\n");
    printf("3: Mostrar Pilha de Comandos\n");
    printf("4: Verificar Status da Pilha\n"); 
    printf("5: Finalizar e sair\n");        
    printf("Escolha uma opcao: ");
}

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}

void liberar_pilha(Pilha *p) {
    int count = 0;
    Feitico f;
    
    do {
        f = pop(p);
        if (f.custo_mana != -1) {
            count++;
        }
    } while (f.custo_mana != -1);

        if (count > 0) {
    }
}