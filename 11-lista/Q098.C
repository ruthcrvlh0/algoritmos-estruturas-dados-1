#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// 1. Struct para representar o Membro (os dados a serem salvos/carregados)
typedef struct {
    int id;
    char nome[100];
    int nivel; 
} Membro;

// 2. Struct para o Nó da Lista
typedef struct no {
    Membro dado;
    struct no *proximo;
} No;

// 3. Struct para a Lista
typedef struct {
    No *inicio;
} Lista;

// --- PROTÓTIPOS ---
void inserir_fim(Lista *lista, Membro m);
void mostrar_guilda(Lista *lista);
void liberar_lista(Lista *lista);
void salvar_guilda_teste(); 
Lista carregar_guilda(); 

// --- IMPLEMENTAÇÃO DA FUNÇÃO AUXILIAR DE TESTE ---

/**
 * @brief Cria e salva uma lista fixa de 3 membros no arquivo guild_roster.b
 * para garantir que a função de carregamento tenha um arquivo de teste.
 */
void salvar_guilda_teste() {
    FILE *arquivo = fopen("guild_roster.b", "wb");
    if (arquivo == NULL) {
        perror("[ERRO] Falha ao criar arquivo de teste");
        exit(EXIT_FAILURE);
    }

    Membro m1 = {1, "Aragorn", 95};
    Membro m2 = {2, "Legolas", 88};
    Membro m3 = {3, "Gimli", 90};

    fwrite(&m1, sizeof(Membro), 1, arquivo);
    fwrite(&m2, sizeof(Membro), 1, arquivo);
    fwrite(&m3, sizeof(Membro), 1, arquivo);

    fclose(arquivo);
    printf("[LOG] Arquivo de teste 'guild_roster.b' criado com 3 membros.\n");
}

// --- FUNÇÃO FOCO: CARREGAR GUILDA DO ARQUIVO BINÁRIO ---

/**
 * @brief Carrega os membros de um arquivo binário e os insere em uma nova lista encadeada.
 * @return A nova lista encadeada preenchida.
 */
Lista carregar_guilda() {
    // b. Cria uma nova lista encadeada vazia
    Lista nova_guilda;
    nova_guilda.inicio = NULL;
    
    // a. Abrir o arquivo em modo de leitura binária ("rb")
    FILE *arquivo = fopen("guild_roster.b", "rb");

    if (arquivo == NULL) {
        perror("[ERRO] Nao foi possivel abrir 'guild_roster.b' para leitura");
        // Retorna uma lista vazia em caso de erro
        return nova_guilda; 
    }

    Membro membro_lido;
    int membros_carregados = 0;

    while (fread(&membro_lido, sizeof(Membro), 1, arquivo) == 1) {
        // d. Para cada membro lido, inseri-lo no final da nova lista
        inserir_fim(&nova_guilda, membro_lido);
        membros_carregados++;
    }

    // e. Fechar o arquivo
    fclose(arquivo);

    printf("\n[SUCESSO] Carregamento concluido. %d membros carregados do arquivo.\n", membros_carregados);
    return nova_guilda; // Retorna a lista preenchida
}

int main() {
    printf("--- Simulacao de Carregamento de Save Game ---\n");
    salvar_guilda_teste();
    Lista guild_roster = carregar_guilda();
    mostrar_guilda(&guild_roster);
    liberar_lista(&guild_roster);
    
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---

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
}

void mostrar_guilda(Lista *lista) {
    printf("\n--- Roster da Guilda Carregado ---\n");
    if (lista->inicio == NULL) {
        printf("A lista de membros esta vazia.\n");
    } else {
        No *aux = lista->inicio;
        while (aux != NULL) {
            printf("ID: %d | Nome: %s | Nivel: %d\n", aux->dado.id, aux->dado.nome, aux->dado.nivel);
            aux = aux->proximo;
        }
    }
    printf("----------------------------------\n");
}

void liberar_lista(Lista *lista) {
    No *atual = lista->inicio;
    No *temp;
    int liberados = 0;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
        liberados++;
    }
    lista->inicio = NULL;
    printf("[LOG] %d nos liberados da memoria.\n", liberados);
}