#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// 1. Struct para representar o Membro (os dados a serem salvos)
typedef struct {
    int id;
    char nome[100];
} Membro;

// 2. Struct para o Nó da Lista (contém os dados e o ponteiro dinâmico)
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
void inicializar_lista(Lista *lista);
void inserir_fim(Lista *lista, Membro m);
void mostrar_lista(Lista *lista);
void liberar_lista(Lista *lista);

// Função foco: Salvar lista em arquivo binário
void salvar_guild_arquivo(Lista lista);

// --- FUNÇÃO FOCO: SALVAR GUILD EM ARQUIVO BINÁRIO ---

/**
 * @brief Percorre a lista encadeada e salva os dados de cada Membro 
 * em um arquivo binário (guild_roster.bin).
 * @param lista A lista de membros a ser salva.
 */
void salvar_guild_arquivo(Lista lista) {
    // 1. Abre o arquivo no modo de escrita binária ("wb")
    FILE *arquivo = fopen("guild_roster.bin", "wb");

    if (arquivo == NULL) {
        perror("[ERRO] Nao foi possivel abrir o arquivo para escrita");
        return;
    }

    if (lista.inicio == NULL) {
        printf("\n[AVISO] A guilda esta vazia. Criando um arquivo vazio.\n");
        fclose(arquivo);
        return;
    }

    No *atual = lista.inicio;
    int membros_salvos = 0;

    // 2. Percorre a lista do início ao fim
    while (atual != NULL) {
        size_t escritos = fwrite(&(atual->dado), sizeof(Membro), 1, arquivo);

        if (escritos != 1) {
            printf("[ERRO] Falha ao escrever o membro ID %d no arquivo.\n", atual->dado.id);
            fclose(arquivo);
            return;
        }

        atual = atual->proximo;
        membros_salvos++;
    }

    // 4. Fecha o arquivo
    fclose(arquivo);
    printf("\n[SUCESSO] %d membros da guilda salvos em 'guild_roster.bin'.\n", membros_salvos);
}

int main() {
    Lista guilda;
    inicializar_lista(&guilda);
    int opcao;
    Membro novo_membro;

    // Adiciona alguns dados iniciais para teste
    inserir_fim(&guilda, (Membro){101, "Ariel"});
    inserir_fim(&guilda, (Membro){102, "Brenda"});

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
                inserir_fim(&guilda, novo_membro);
                break;
            case 2:
                mostrar_lista(&guilda);
                break;
            case 3:
                salvar_guild_arquivo(guilda);
                break;
            case 4:
                printf("\nSaindo do gerenciador de guilda.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 4);

    liberar_lista(&guilda);
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---

void menu() {
    printf("\n--- Gerenciador de Guilda ---\n");
    printf("1. Adicionar Membro\n");
    printf("2. Mostrar Registro\n");
    printf("3. Salvar Guilda em Arquivo Binario\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
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
    printf("[LOG] Membro %s (ID %d) contratado.\n", m.nome, m.id);
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

void liberar_lista(Lista *lista) {
    No *atual = lista->inicio;
    No *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    printf("\n[LOG] Memoria da guilda liberada.\n");
}