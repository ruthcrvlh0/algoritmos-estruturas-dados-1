#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
} Heroi;

typedef struct no {
    Heroi dado;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
} Lista;

Lista* inicializar_lista() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        perror("Erro ao alocar memoria para a lista");
        exit(EXIT_FAILURE);
    }
    nova_lista->inicio = NULL;
    return nova_lista;
}

No* criar_novo_no(Heroi heroi) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return NULL;
    }
    novo_no->dado = heroi;
    novo_no->proximo = NULL;
    return novo_no;
}

/**
 * @brief Adiciona um herói no FIM da formação.
 */
void adicionar_no_fim(Lista *lista, Heroi heroi) {
    No *novo_no = criar_novo_no(heroi);
    if (novo_no == NULL) return;

    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
    } else {
        No *atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }

    printf("\n[LOG] Heroi '%s' (ID %d) adicionado ao final da formacao.\n", heroi.nome, heroi.id);
}

/**
 * @brief Exibe a formação atual.
 */
void mostrar_formacao(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nA formacao de batalha esta vazia.\n");
        return;
    }

    No *atual = lista->inicio;
    printf("\n--- Formacao de Batalha (Frente para Tras) ---\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->dado.id, atual->dado.nome);
        atual = atual->proximo;
    }
    printf("----------------------------------------------\n");
}

/**
 * @brief Insere um novo herói (guarda-costas) ANTES do herói VIP identificado pelo ID.
 * @return 1 se a inserção foi bem-sucedida, 0 caso contrário.
 */
int inserir_antes(Lista *lista, Heroi guarda_costas, int id_vip) {
    No *novo_no = criar_novo_no(guarda_costas);
    if (novo_no == NULL) return 0;

    if (lista->inicio == NULL) {
        printf("\n[ERRO] Formacao vazia. VIP nao encontrado.\n");
        free(novo_no);
        return 0;
    }

    if (lista->inicio->dado.id == id_vip) {
        novo_no->proximo = lista->inicio;
        lista->inicio = novo_no;
        printf("\n[SUCESSO] Guarda-Costas '%s' (ID %d) inserido na FRENTE do VIP.\n", guarda_costas.nome, guarda_costas.id);
        return 1;
    }

    No *anterior = lista->inicio;
    No *atual = lista->inicio->proximo;

    while (atual != NULL && atual->dado.id != id_vip) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n[ERRO] Heroi VIP com ID %d NÃO encontrado na formacao. Insercao abortada.\n", id_vip);
        free(novo_no);
        return 0;
    }

    novo_no->proximo = atual;
    anterior->proximo = novo_no;
    
    printf("\n[SUCESSO] Guarda-Costas '%s' (ID %d) inserido ANTES do VIP (ID %d).\n", 
           guarda_costas.nome, guarda_costas.id, id_vip);
    return 1;
}

void liberar_lista(Lista *lista) {
    No *atual = lista->inicio;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int main() {
    Lista *formacao = inicializar_lista();
    int opcao;
    Heroi novo_heroi;
    int id_vip;

    do {
        printf("\n--- Gerenciador de Formacao de Batalha ---\n");
        printf("1 - Adicionar Heroi no Fim (Reforco)\n");
        printf("2 - Adicionar Guarda-Costas (Inserir Antes do VIP)\n");
        printf("3 - Mostrar Formacao\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\n--- Novo Heroi ---\n");
                printf("ID: ");
                scanf("%d", &novo_heroi.id);
                printf("Nome (sem espacos): ");
                scanf("%s", novo_heroi.nome);
                adicionar_no_fim(formacao, novo_heroi);
                break;
                
            case 2:
                printf("\n--- Adicionar Guarda-Costas ---\n");
                printf("ID do Guarda-Costas: ");
                scanf("%d", &novo_heroi.id);
                printf("Nome do Guarda-Costas: ");
                scanf("%s", novo_heroi.nome);
                
                printf("ID do Heroi VIP a ser protegido (insercao ANTES): ");
                scanf("%d", &id_vip);
                
                inserir_antes(formacao, novo_heroi, id_vip);
                break;
                
            case 3:
                mostrar_formacao(formacao);
                break;
                
            case 4:
                printf("\nEncerrando o gerenciador de formacao.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1, 2, 3 ou 4.\n");
                break;
        }
    } while (opcao != 4);

    liberar_lista(formacao);
    
    return 0;
}