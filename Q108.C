#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// 1. Struct para representar o Jogador (dado)
typedef struct {
    int id;
    char nickname[50];
} Jogador;

// 2. Struct para o Nó da Fila
typedef struct no {
    Jogador dado;
    struct no *prox;
} No;

// 3. Struct para a Fila (Controle do Início e Fim)
typedef struct {
    No *inicio; // Ponteiro para o primeiro elemento (quem sai - Dequeue)
    No *fim;    // Ponteiro para o último elemento (quem entra - Enqueue)
} Fila;

// --- PROTÓTIPOS ---
void menu();
void inicializar_fila(Fila *f);
void inserir(Fila *f, Jogador j); // Função foco: Enqueue
void liberar_fila(Fila *f);

// --- FUNÇÃO FOCO: INSERIR (Enqueue) ---

/**
 * @brief Adiciona um novo jogador ao final da fila (operação ENQUEUE).
 * @param f Ponteiro para a Fila.
 * @param j Dados do Jogador a ser inserido.
 */
void inserir(Fila *f, Jogador j) {
    // 1. Aloca memória para o novo nó
    No *novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("[ERRO] Falha na alocacao de memoria para o jogador.\n");
        return;
    }

    // 2. Preenche os dados e ajusta o ponteiro
    novo_no->dado = j;
    novo_no->prox = NULL; // Novo nó sempre será o último

    // 3. Verifica o caso de Fila VAZIA
    if (f->inicio == NULL) {
        // Se a fila estava vazia, o novo nó é o primeiro (inicio) e o último (fim)
        f->inicio = novo_no;
        f->fim = novo_no;
    } 
    // 4. Caso de Fila NÃO-VAZIA
    else {
        // O nó que atualmente é o fim deve apontar para o novo nó
        f->fim->prox = novo_no;
        
        // O novo nó se torna o novo fim da fila
        f->fim = novo_no;
    }
    
    printf("[LOG] Jogador %s (ID %d) entrou na fila de matchmaking.\n", j.nickname, j.id);
}

// --- FUNÇÃO PRINCIPAL ---
int main() {
    Fila fila_matchmaking;
    inicializar_fila(&fila_matchmaking);
    int op;
    Jogador novo_jogador;

    do {
        menu();
        if (scanf("%d", &op) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(op) {
            case 1:
                printf("\n--- Novo Jogador na Fila ---\n");
                printf("ID do Jogador: ");
                scanf("%d", &novo_jogador.id);
                printf("Nickname: ");
                scanf("%49s", novo_jogador.nickname);
                inserir(&fila_matchmaking, novo_jogador);
                break;
                
            case 2:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(op != 2);

    liberar_fila(&fila_matchmaking);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---

void menu() {
    printf("\n--- Fila de Matchmaking MOBA ---\n");
    printf("1: Adicionar Jogador (ENQUEUE)\n");
    printf("2: Sair\n");
    printf("Escolha uma opcao: ");
}

void inicializar_fila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void liberar_fila(Fila *f) {
    No *atual = f->inicio;
    No *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    f->inicio = NULL;
    f->fim = NULL;
    printf("[LOG] Memoria da fila liberada.\n");
}