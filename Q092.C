#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// 1. Struct para representar o Mercenário
typedef struct {
    int id;
    char nome[50];
} Mercenario;

// 2. Struct para o Nó da Lista
typedef struct no {
    Mercenario dado;
    struct no *proximo;
} No;

// 3. Struct para a Lista (Companhia de Mercenários)
typedef struct {
    No *inicio;
} Lista;

// --- PROTÓTIPOS ---
void menu();
Lista* inicializar_lista();
void contratar_mercenario(Lista *lista, Mercenario m);
void exibir_companhia(Lista *lista);
void demitir_todos_mercenarios(Lista *lista); // Função foco

// --- IMPLEMENTAÇÃO DA FUNÇÃO PRINCIPAL ---

int main() {
    Lista *companhia = inicializar_lista();
    int opcao;
    Mercenario novo_mercenario;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n');
            opcao = 0;
            continue;
        }

        switch(opcao) {
            case 1:
                printf("\n--- Contratar Mercenario ---\n");
                printf("ID: ");
                scanf("%d", &novo_mercenario.id);
                printf("Nome (sem espacos): ");
                scanf("%49s", novo_mercenario.nome);
                contratar_mercenario(companhia, novo_mercenario);
                break;
            case 2:
                exibir_companhia(companhia);
                break;
            case 3:
                demitir_todos_mercenarios(companhia);
                break;
            case 4:
                printf("\nSaindo do gerenciador de companhia.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 4);
    free(companhia);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---

void menu() {
    printf("\n--- Gerenciador de Mercenarios ---\n");
    printf("1. Contratar mercenario (Inserir no fim)\n");
    printf("2. Exibir companhia\n");
    printf("3. Declarar falencia (Deletar lista inteira)\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

Lista* inicializar_lista() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) exit(EXIT_FAILURE);
    nova_lista->inicio = NULL;
    return nova_lista;
}

void contratar_mercenario(Lista *lista, Mercenario m) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("[ERRO] Erro de alocacao de memoria!\n");
        return;
    }
    novo->dado = m;
    novo->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *aux = lista->inicio;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    printf("[LOG] Mercenario %s (ID %d) contratado.\n", m.nome, m.id);
}

void exibir_companhia(Lista *lista) {
    printf("\n--- Companhia de Mercenarios ---\n");
    if (lista->inicio == NULL) {
        printf("A companhia esta dissolvida (lista vazia).\n");
    } else {
        No *aux = lista->inicio;
        while (aux != NULL) {
            printf("ID: %d, Nome: %s\n", aux->dado.id, aux->dado.nome);
            aux = aux->proximo;
        }
    }
    printf("--------------------------------\n");
}

/**
 * @brief Libera toda a memória alocada para os nós da lista encadeada.
 * Evita vazamentos de memória.
 */
void demitir_todos_mercenarios(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\n[AVISO] A companhia ja estava dissolvida (lista vazia).\n");
        return;
    }

    No *atual = lista->inicio;
    No *proximo_no;
    int contador = 0;

    printf("\n>>> DECLARANDO FALENCIA: Demitindo todos os mercenarios... <<<\n");

    while (atual != NULL) {
        proximo_no = atual->proximo; 
        
        free(atual);                 
        atual = proximo_no;          
        contador++;
    }

    lista->inicio = NULL; 

    printf("\n[SUCESSO] %d mercenarios foram demitidos e a memoria liberada.\n", contador);
    
    if (lista->inicio == NULL) {
        printf("COMPANHIA DISSOLVIDA. A lista esta agora VAZIA.\n");
    }
}