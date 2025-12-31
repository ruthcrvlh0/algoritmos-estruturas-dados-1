#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// 1. Struct para representar o Membro
typedef struct {
    int id;
    char nome[100];
} Membro;

// 2. Struct para o Nó da Lista
typedef struct no {
    Membro dado;
    struct no *proximo;
} No;

// 3. Struct para a Lista (Registro da Guilda)
typedef struct {
    No *inicio;
} Lista;

// --- PROTÓTIPOS ---
void menu();
Lista* inicializar_lista();
void inserir_fim(Lista *lista, Membro m);
void mostrar_lista(Lista *lista);
No* pesquisar_membro(Lista *lista, int id); 
void alterar_nome(Lista *lista, int id, char novo_nome[]); 
void liberar_lista(Lista *lista);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    Lista *guilda = inicializar_lista();
    int opcao, id_alvo;
    Membro novo_membro;
    char novo_nome_input[100];

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {
            case 1:
                printf("\n--- Novo Membro ---\n");
                printf("ID do Membro: ");
                scanf("%d", &novo_membro.id);
                printf("Nome: ");
                scanf("%99s", novo_membro.nome);
                inserir_fim(guilda, novo_membro);
                break;
            case 2:
                mostrar_lista(guilda);
                break;
            case 3:
                printf("\n--- Alterar Nome ---\n");
                printf("Digite o ID do membro a ser renomeado: ");
                scanf("%d", &id_alvo);
                printf("Digite o NOVO nome: ");
                scanf("%99s", novo_nome_input);
                alterar_nome(guilda, id_alvo, novo_nome_input);
                break;
            case 4:
                printf("\nSaindo do gerenciador de guilda...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 4);

    liberar_lista(guilda);
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void menu() {
    printf("\n--- Gerenciador de Guilda ---\n");
    printf("1. Adicionar Membro\n");
    printf("2. Mostrar Registro\n");
    printf("3. Alterar Nome de Membro por ID\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

Lista* inicializar_lista() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) exit(EXIT_FAILURE);
    nova_lista->inicio = NULL;
    return nova_lista;
}

void liberar_lista(Lista *lista) {
    No *atual = lista->inicio;
    No *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
}

void inserir_fim(Lista *lista, Membro m) {
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
    printf("[LOG] Membro %s (ID %d) adicionado.\n", m.nome, m.id);
}

void mostrar_lista(Lista *lista) {
    printf("\n--- Registro da Guilda ---\n");
    if (lista->inicio == NULL) {
        printf("Nenhum membro registrado.\n");
    } else {
        No *aux = lista->inicio;
        while (aux != NULL) {
            printf("ID: %d | Nome: %s\n", aux->dado.id, aux->dado.nome);
            aux = aux->proximo;
        }
    }
    printf("--------------------------\n");
}

// --- FUNÇÃO AUXILIAR DE PESQUISA ---

/**
 * @brief Procura um nó pelo ID do membro.
 * @return Ponteiro para o nó (No*) se encontrado, ou NULL.
 */
No* pesquisar_membro(Lista *lista, int id) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado.id == id) {
            return atual; 
        }
        atual = atual->proximo;
    }
    return NULL; 
}

/**
 * @brief Altera o nome de um membro da guilda baseado no ID.
 */
void alterar_nome(Lista *lista, int id, char novo_nome[]) {
    No *membro_no = pesquisar_membro(lista, id);

    if (membro_no != NULL) {
        char nome_antigo[100];
        strcpy(nome_antigo, membro_no->dado.nome);

        strcpy(membro_no->dado.nome, novo_nome);
        
        printf("\n[SUCESSO] Nome do membro ID %d alterado.\n", id);
        printf("  Nome Antigo: %s\n", nome_antigo);
        printf("  Novo Nome:   %s\n", membro_no->dado.nome);
    } else {
        printf("\n[ERRO] Membro com ID %d nao encontrado no registro da guilda.\n", id);
    }
}