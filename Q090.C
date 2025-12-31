#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Struct para representar o Ward
typedef struct {
    int id;
    char nome[100];
} Ward;

// 2. Struct para o Nó da Lista
typedef struct no {
    Ward dado;
    struct no *proximo;
} No;

// 3. Struct para a Lista (Sequência de Wards)
typedef struct {
    No *inicio;
} Lista;

// --- Funções Auxiliares ---

Lista* inicializar_lista() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) exit(EXIT_FAILURE);
    nova_lista->inicio = NULL;
    return nova_lista;
}

No* criar_novo_no(Ward ward) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o no");
        return NULL;
    }
    novo_no->dado = ward;
    novo_no->proximo = NULL;
    return novo_no;
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

// --- 1. Adicionar Ward (Inserir no Fim) ---

void adicionar_ward(Lista *lista, Ward ward) {
    No *novo_no = criar_novo_no(ward);
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
    printf("\n[LOG] Ward '%s' (ID %d) conjurado.\n", ward.nome, ward.id);
}

// --- 3. Mostrar Wards Ativos ---

void mostrar_wards(const Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nNenhum Ward ativo.\n");
        return;
    }

    No *atual = lista->inicio;
    printf("\n--- Wards Ativos (Sequencia) ---\n");
    while (atual != NULL) {
        printf("[ID: %d] %s -> ", atual->dado.id, atual->dado.nome);
        atual = atual->proximo;
    }
    printf("FIM\n");
    printf("--------------------------------\n");
}

// --- 2. Lançar 'Ward Shatter' (Deletar Após um ID Específico) ---

/**
 * @brief Lança o feitiço 'Ward Shatter', deletando o Ward que está após o Ward de referência (ID).
 * @return 1 se a remoção foi bem-sucedida, 0 caso contrário.
 */
int ward_shatter(Lista *lista, int id_referencia) {
    // Caso 1: Lista Vazia
    if (lista->inicio == NULL) {
        printf("\n[ERRO] Nao ha Wards ativos. Ward Shatter falhou.\n");
        return 0;
    }

    // 1. Encontrar o Ward de Referência
    No *referencia = lista->inicio;
    while (referencia != NULL && referencia->dado.id != id_referencia) {
        referencia = referencia->proximo;
    }

    // Caso 2: Ward de Referência não encontrado
    if (referencia == NULL) {
        printf("\n[ERRO] Ward de referencia com ID %d nao encontrado. Ward Shatter falhou.\n", id_referencia);
        return 0;
    }

    // Caso 3: Ward de Referência é o último (não há nó após ele)
    if (referencia->proximo == NULL) {
        printf("\n[ERRO] Ward %s (ID %d) e o ultimo. Nao ha Ward apos ele para ser destruido. Ward Shatter falhou.\n", 
               referencia->dado.nome, id_referencia);
        return 0;
    }

    // 2. Deletar o nó seguinte (o alvo)
    No *alvo = referencia->proximo;
    
    // 3. Reconectar a lista
    referencia->proximo = alvo->proximo;
    
    printf("\n[SUCESSO] Ward Shatter lançado! Ward %s (ID %d) foi DESTRUIDO apos o Ward %d.\n", 
           alvo->dado.nome, alvo->dado.id, id_referencia);
    
    // 4. Liberar memória
    free(alvo);
    return 1;
}

int main() {
    Lista *wards = inicializar_fila();
    int opcao;
    Ward novo_ward;
    int id_alvo_shatter;

    do {
        printf("\n--- Gerenciador de Wards Magicos ---\n");
        printf("1: Adicionar Ward\n");
        printf("2: Lancar 'Ward Shatter' (Deletar Apos ID)\n");
        printf("3: Mostrar Wards Ativos\n");
        printf("4: Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0; 
            continue;
        }

        switch (opcao) {
            case 1:
                // Adicionar Ward
                printf("\n--- Conjurando Novo Ward ---\n");
                printf("ID do Ward: ");
                scanf("%d", &novo_ward.id);
                printf("Nome do Ward (sem espacos): ");
                scanf("%99s", novo_ward.nome);
                adicionar_ward(wards, novo_ward);
                break;
                
            case 2:
                // Lançar Ward Shatter
                printf("\n--- Lancar Ward Shatter ---\n");
                printf("Digite o ID do Ward de referencia: ");
                if (scanf("%d", &id_alvo_shatter) == 1) {
                    ward_shatter(wards, id_alvo_shatter);
                }
                break;
                
            case 3:
                // Mostrar Wards
                mostrar_wards(wards);
                break;
                
            case 4:
                printf("\nEncerrando o sistema magico.\n");
                break;
                
            default:
                printf("\nOpcao invalida. Digite 1, 2, 3 ou 4.\n");
                break;
        }
    } while (opcao != 4);

    liberar_lista(wards);
    
    return 0;
}