#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
} Item;

typedef struct no {
    Item dado;
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

No* criar_novo_no(Item item) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return NULL;
    }
    novo_no->dado = item;
    novo_no->proximo = NULL;
    return novo_no;
}


/**
 * @brief Insere um item no INÍCIO da lista.
 */
void inserir_no_inicio(Lista *lista, Item item) {
    No *novo_no = criar_novo_no(item);
    if (novo_no == NULL) return;

    novo_no->proximo = lista->inicio;
    lista->inicio = novo_no;

    printf("\n[LOG] Item '%s' (ID %d) inserido no INICIO.\n", item.nome, item.id);
}

/**
 * @brief Insere um item no FIM da lista.
 */
void inserir_no_fim(Lista *lista, Item item) {
    No *novo_no = criar_novo_no(item);
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

    printf("\n[LOG] Item '%s' (ID %d) inserido no FIM.\n", item.nome, item.id);
}


/**
 * @brief Exibe todos os itens no inventário.
 */
void mostrar_inventario(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nO inventário de missoes esta vazio.\n");
        return;
    }

    No *atual = lista->inicio;
    printf("\n--- Inventário de Missões ---\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", 
               atual->dado.id, atual->dado.nome);
        
        atual = atual->proximo;
    }
    printf("-------------------------------\n");
}


/**
 * @brief Insere um novo item APÓS um item existente com um ID específico.
 * @return 1 se a inserção foi bem-sucedida, 0 caso contrário.
 */
int inserir_apos_fragmento(Lista *lista, Item catalisador, int id_fragmento) {
    if (lista->inicio == NULL) {
        printf("\n[ERRO] Inventário vazio. Insercao apos o fragmento %d impossível.\n", id_fragmento);
        return 0;
    }

    No *fragmento = lista->inicio;
    while (fragmento != NULL && fragmento->dado.id != id_fragmento) {
        fragmento = fragmento->proximo;
    }

    if (fragmento == NULL) {
        printf("\n[ERRO] Fragmento de Poder com ID %d NÃO encontrado. Insercao abortada.\n", id_fragmento);
        return 0;
    }

    No *novo_no = criar_novo_no(catalisador);
    if (novo_no == NULL) return 0;

    novo_no->proximo = fragmento->proximo;
    
    fragmento->proximo = novo_no;

    printf("\n[SUCESSO] '%s' (ID %d) inserido APÓS o Fragmento %d.\n", 
           catalisador.nome, catalisador.id, id_fragmento);
    return 1;
}

int main() {
    Lista *inventario = inicializar_lista();
    int opcao;
    Item novo_item;
    int id_fragmento;

    do {
        printf("\n--- Gerenciador de Inventario (Itens de Missao) ---\n");
        printf("1 - Inserir item no inicio (Comum)\n");
        printf("2 - Inserir item no fim (Comum)\n");
        printf("3 - Inserir catalisador APOS um fragmento (Foco)\n");
        printf("4 - Mostrar inventário\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
            case 2:
                printf("\nDigite o ID do item: ");
                scanf("%d", &novo_item.id);
                printf("Digite o nome do item (sem espacos): ");
                scanf("%s", novo_item.nome);
                
                if (opcao == 1) {
                    inserir_no_inicio(inventario, novo_item);
                } else {
                    inserir_no_fim(inventario, novo_item);
                }
                break;
                
            case 3:
                printf("\n--- Inserir Catalisador ---\n");
                printf("ID do Catalisador Rúnico: ");
                scanf("%d", &novo_item.id);
                strcpy(novo_item.nome, "CatalisadorRunico"); // Nome padrão
                
                printf("ID do Fragmento APOS o qual o catalisador sera inserido: ");
                scanf("%d", &id_fragmento);
                
                inserir_apos_fragmento(inventario, novo_item, id_fragmento);
                break;
                
            case 4:
                mostrar_inventario(inventario);
                break;
                
            case 5:
                printf("\nEncerrando o gerenciador de inventario.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite de 1 a 5.\n");
                break;
        }
    } while (opcao != 5);

    liberar_lista(inventario);
    
    return 0;
}