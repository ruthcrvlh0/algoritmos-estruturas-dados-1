#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// 1. Struct para representar o Feitiço (dado)
typedef struct {
    char nome[50];
    int custo_mana;
} Feitico;

// 2. Struct para o Nó da Pilha
typedef struct no {
    Feitico dado;
    struct no *prox;
} No;

// 3. Struct para a Pilha (Controle do Topo)
typedef struct {
    No *topo;
} Pilha;

// --- PROTÓTIPOS ---
void menu();
void inicializar_pilha(Pilha *p);
void push(Pilha *p, Feitico f); 
Feitico pop(Pilha *p);          
void mostrar_pilha(Pilha *p);
void liberar_pilha(Pilha *p);  

// --- FUNÇÃO FOCO: POP (Lançar Feitiço) ---

/**
 * @brief Remove e retorna o feitiço do topo da pilha (operação POP).
 * Simula a execução do feitiço mais recente.
 * @param p Ponteiro para a Pilha.
 * @return A struct Feitico removida, ou uma Feitico de falha (custo_mana = -1) se vazia.
 */
Feitico pop(Pilha *p) {
    // Feitiço de falha (sentinela)
    Feitico falha;
    strcpy(falha.nome, "NENHUM");
    falha.custo_mana = -1; 
    
    // 1. Verifica se a pilha está vazia
    if (p->topo == NULL) {
        printf("\n[ERRO] A pilha de comandos esta vazia! Nao ha feitiços para lancar.\n");
        return falha;
    }

    // 2. Armazena o nó a ser removido e os dados a serem retornados
    No *no_removido = p->topo;
    Feitico lancado = no_removido->dado;

    // 3. Atualiza o topo: o topo agora é o próximo nó
    p->topo = no_removido->prox;

    // 4. Libera a memória do nó removido
    free(no_removido);
    
    return lancado;
}

void menu() {
    printf("\n--- Pilha de Comandos do Arcanista ---\n");
    printf("1: Adicionar um novo feitiço (PUSH)\n");
    printf("2: Lançar Próximo Feitiço (POP)\n"); 
    printf("3: Mostrar Pilha de Comandos\n");
    printf("4: Finalizar e sair\n");
    printf("Escolha uma opcao: ");
}

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
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

void mostrar_pilha(Pilha *p) {
    if (p->topo == NULL) {
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
    int count = 0;
    Feitico f;
    
    do {
        f = pop(p);
        if (f.custo_mana != -1) {
            count++;
        }
    } while (f.custo_mana != -1);
    
    printf("\n[LOG] Memoria da pilha de comandos liberada. %d feitiços removidos via POP.\n", count);
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
                
            case 4: // SAIR
                printf("\nFinalizando o sistema de comando. O Arcanista descansa.\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(op != 4);
    liberar_pilha(&comandos_arcanista);

    return 0;
}