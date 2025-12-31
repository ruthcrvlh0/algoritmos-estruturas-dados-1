#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- ESTRUTURAS ---

typedef struct {
    int id_ameaca; 
    char nome[50];
} Monstro;

typedef struct no {
    Monstro dado;
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
} Lista;

// --- PROTÓTIPOS ---
void menu();
Lista* inicializar_lista();
void adicionarMonstro(Lista *lista, Monstro m);
void mostrarBestiario(Lista *lista);
void ordenarBestiario(Lista *lista); 
void liberar_lista(Lista *lista);

// --- FUNÇÃO FOCO: ORDENAÇÃO (Bubble Sort) ---

/**
 * @brief Ordena a lista encadeada usando o algoritmo Bubble Sort
 * com base no id_ameaca (Nível de Ameaça) em ordem crescente.
 */
void ordenarBestiario(Lista *lista) {
    if (lista->inicio == NULL || lista->inicio->proximo == NULL) {
        printf("\n[AVISO] Bestiario vazio ou com apenas um monstro. Nao ha necessidade de ordenar.\n");
        return;
    }

    bool trocado;
    No *ptr1;
    No *lptr = NULL; 
    printf("\n[LOG] Iniciando a ordenacao do Bestiario (Bubble Sort por Nivel de Ameaça).\n");
    
    do {
        trocado = false;
        ptr1 = lista->inicio;

        while (ptr1->proximo != lptr) {
            
            if (ptr1->dado.id_ameaca > ptr1->proximo->dado.id_ameaca) {
                
                Monstro temp = ptr1->dado;
                ptr1->dado = ptr1->proximo->dado;
                ptr1->proximo->dado = temp;
                
                trocado = true;
            }
            ptr1 = ptr1->proximo;
        }
        lptr = ptr1;

    } while (trocado);

    printf("[SUCESSO] Bestiario ordenado com sucesso em ordem crescente de Nivel de Ameaça.\n");
}

int main() {
    Lista *bestiario = inicializar_lista();
    int opcao;
    Monstro novo_monstro;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {
            case 1:
                printf("\n--- Novo Registro de Monstro ---\n");
                printf("Nivel de Ameaça (ID): ");
                scanf("%d", &novo_monstro.id_ameaca);
                printf("Nome do Monstro (sem espacos): ");
                scanf("%49s", novo_monstro.nome);
                adicionarMonstro(bestiario, novo_monstro);
                break;
            case 2:
                ordenarBestiario(bestiario);
                break;
            case 3:
                mostrarBestiario(bestiario);
                break;
            case 4:
                printf("\nSaindo do Bestiario...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 4);

    liberar_lista(bestiario);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ---

void menu() {
    printf("\n--- Gerenciador de Bestiario ---\n");
    printf("1. Adicionar Monstro (Fim)\n");
    printf("2. Ordenar Bestiario (Bubble Sort por Ameaça)\n");
    printf("3. Mostrar Bestiario\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

Lista* inicializar_lista() {
    Lista *nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) exit(EXIT_FAILURE);
    nova_lista->inicio = NULL;
    return nova_lista;
}

void adicionarMonstro(Lista *lista, Monstro m) {
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
    printf("[LOG] Monstro '%s' (Ameaça: %d) adicionado.\n", m.nome, m.id_ameaca);
}

void mostrarBestiario(Lista *lista) {
    printf("\n--- Registro do Bestiario ---\n");
    if (lista->inicio == NULL) {
        printf("Nenhum monstro registrado.\n");
    } else {
        No *aux = lista->inicio;
        while (aux != NULL) {
            printf("Ameaça ID: %d | Nome: %s\n", aux->dado.id_ameaca, aux->dado.nome);
            aux = aux->proximo;
        }
    }
    printf("------------------------------\n");
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