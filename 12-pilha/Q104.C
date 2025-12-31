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
int vazia(Pilha *p);
void push(Pilha *p, Feitico f); 
Feitico pop(Pilha *p);
Feitico top(Pilha *p);          
void mostrar_pilha(Pilha *p);
void liberar_pilha(Pilha *p);

/**
 * @brief Retorna o feitiço no topo da pilha SEM removê-lo.
 * @param p Ponteiro para a Pilha.
 * @return A struct Feitico do topo, ou uma Feitico de falha (custo_mana = -1) se vazia.
 */
Feitico top(Pilha *p) {
    Feitico falha;
    strcpy(falha.nome, "NENHUM");
    falha.custo_mana = -1; 
    
    if (vazia(p)) {
        printf("\n[ERRO] A pilha de comandos esta vazia. Nao ha feitiços para consultar.\n");
        return falha;
    }

    return p->topo->dado;
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
            case 1: // PUSH
                printf("\n--- Novo Comando de Feitiço ---\n");
                printf("Nome do Feitiço: ");
                scanf("%49s", novo_feitico.nome);
                printf("Custo de Mana: ");
                scanf("%d", &novo_feitico.custo_mana);
                push(&comandos_arcanista, novo_feitico);
                break;
                
            case 2: { // POP
                Feitico resultado = pop(&comandos_arcanista);
                if (resultado.custo_mana != -1) {
                    printf("\n[SUCESSO] Feitiço '%s' (Custo: %d) lançado com sucesso!\n", 
                           resultado.nome, resultado.custo_mana);
                }
                break;
            }
                
            case 3: // MOSTRAR PILHA
                mostrar_pilha(&comandos_arcanista);
                break;
            
            case 4: { // NOVO: TOP (CONSULTAR PRÓXIMO)
                Feitico proximo = top(&comandos_arcanista);
                if (proximo.custo_mana != -1) {
                    printf("\n--- Consulta: Proximo Feitiço ---\n");
                    printf("  Feitiço: %s | Custo de Mana: %d\n", proximo.nome, proximo.custo_mana);
                    printf("-----------------------------------\n");
                }
                break;
            }
                
            case 5: { // VERIFICAR STATUS (Opção ajustada)
                printf("\n--- Status da Pilha de Comandos ---\n");
                if (vazia(&comandos_arcanista)) {
                    printf("Status: A pilha de comandos está VAZIA. Nenhuma ação pendente.\n");
                } else {
                    printf("Status: A pilha de comandos possui feitiços pendentes.\n");
                }
                break;
            }
                
            case 6: // SAIR (Opção ajustada)
                printf("\nFinalizando o sistema de comando. O Arcanista descansa.\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(op != 6);

    liberar_pilha(&comandos_arcanista);
    return 0;
}

// --- FUNÇÕES REUTILIZADAS ---

void menu() {
    printf("\n--- Pilha de Comandos do Arcanista ---\n");
    printf("1: Adicionar um novo feitiço (PUSH)\n");
    printf("2: Lançar Próximo Feitiço (POP)\n");
    printf("3: Mostrar Pilha de Comandos\n");
    printf("4: Consultar Próximo Feitiço (TOP/PEEK)\n"); 
    printf("5: Verificar Status da Pilha\n");
    printf("6: Finalizar e sair\n"); 
    printf("Escolha uma opcao: ");
}

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}

int vazia(Pilha *p) {
    return (p->topo == NULL);
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

Feitico pop(Pilha *p) {
    Feitico falha;
    strcpy(falha.nome, "NENHUM");
    falha.custo_mana = -1; 
    
    if (vazia(p)) {
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

void liberar_pilha(Pilha *p) {
    Feitico f;
    do {
        f = pop(p);
    } while (f.custo_mana != -1);
}