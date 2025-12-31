#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estruturas de Dados ---

typedef struct {
    int id;
    char nickname[50];
} Jogador;

typedef struct no {
    Jogador dados;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

// --- Protótipos ---
void criarFila(Fila *f);
void entrar(Fila *f, int id, char *nick);
void mostrar(Fila *f);
Jogador remover(Fila *f);
int estaVazia(Fila *f);
Jogador verInicio(Fila *f);
void salvarFila(Fila *f, const char *nomeArquivo);
void carregarFila(Fila *f, const char *nomeArquivo); 

// --- Implementações ---

void criarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int estaVazia(Fila *f) {
    return (f->inicio == NULL);
}

void entrar(Fila *f, int id, char *nick) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }
    novo->dados.id = id;
    strcpy(novo->dados.nickname, nick);
    novo->proximo = NULL;

    if (estaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    f->fim = novo;
    printf(">> Jogador %s (ID: %d) entrou na fila.\n", nick, id);
}

void mostrar(Fila *f) {
    if (estaVazia(f)) {
        printf("\n>> A fila de matchmaking esta vazia.\n");
        return;
    }
    No *aux = f->inicio;
    printf("\n--- Fila Atual ---\n");
    while (aux != NULL) {
        printf("ID: %d | Nick: %s\n", aux->dados.id, aux->dados.nickname);
        aux = aux->proximo;
    }
    printf("------------------\n");
}

Jogador remover(Fila *f) {
    if (estaVazia(f)) {
        printf("\n>> Erro: Fila vazia!\n");
        Jogador jVazio; jVazio.id = -1; 
        return jVazio;
    }
    No *noRemover = f->inicio;
    Jogador dadosJogador = noRemover->dados;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(noRemover);
    return dadosJogador;
}

Jogador verInicio(Fila *f) {
    if (estaVazia(f)) {
        Jogador jVazio; jVazio.id = -1; 
        return jVazio;
    }
    return f->inicio->dados;
}

void salvarFila(Fila *f, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("\n>> Erro ao criar arquivo de backup!\n");
        return;
    }
    No *aux = f->inicio;
    while (aux != NULL) {
        fwrite(&aux->dados, sizeof(Jogador), 1, arquivo);
        aux = aux->proximo;
    }
    fclose(arquivo);
    printf("\n>> Fila salva com sucesso em '%s'.\n", nomeArquivo);
}

void carregarFila(Fila *f, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("\n>> Nenhum arquivo de backup encontrado. Iniciando fila nova.\n");
        return;
    }

    printf("\n>> Arquivo de backup encontrado! Carregando dados...\n");

    Jogador jTemp;

    while (fread(&jTemp, sizeof(Jogador), 1, arquivo) == 1) {
        entrar(f, jTemp.id, jTemp.nickname);
    }

    fclose(arquivo);
    printf(">> Carregamento concluido!\n");
}


int main() {
    Fila filaMatchmaking;
    criarFila(&filaMatchmaking);

    carregarFila(&filaMatchmaking, "matchmaking_queue.bin");

    int opcao, id;
    char nickname[50];
    Jogador jTemp;

    do {
        printf("\n=== SISTEMA DE MATCHMAKING ===\n");
        printf("1. Adicionar Jogador\n");
        printf("2. Mostrar Fila\n");
        printf("3. Remover Jogador\n");
        printf("4. Verificar Vazio\n");
        printf("5. Ver Proximo\n");
        printf("6. Salvar Fila\n");
        printf("7. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("ID: "); scanf("%d", &id);
                printf("Nick: "); scanf(" %[^\n]", nickname);
                entrar(&filaMatchmaking, id, nickname);
                break;
            case 2: mostrar(&filaMatchmaking); break;
            case 3:
                jTemp = remover(&filaMatchmaking);
                if (jTemp.id != -1) printf("\n>> SUCESSO! %s saiu.\n", jTemp.nickname);
                break;
            case 4:
                if (estaVazia(&filaMatchmaking)) printf(">> Vazia.\n"); else printf(">> Com jogadores.\n");
                break;
            case 5:
                jTemp = verInicio(&filaMatchmaking);
                if (jTemp.id != -1) printf(">> Proximo: %s\n", jTemp.nickname);
                break;
            case 6:
                if (estaVazia(&filaMatchmaking)) printf(">> Vazia. Nada a salvar.\n");
                else salvarFila(&filaMatchmaking, "matchmaking_queue.bin");
                break;
            case 7: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}