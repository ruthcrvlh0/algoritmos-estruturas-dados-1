#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    int forca;
    int agilidade;
    int inteligencia;
} Personagem;

int buscar_personagem(const Personagem *personagens, int total, int id_busca);

int main() {
    int n;
    int i;
    int opcao;
    
    printf("--- Ferramenta de Consulta do Mestre do Jogo ---\n");

    printf("Digite o numero total de personagens na campanha: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero de personagens invalido. Encerrando.\n");
        return 1;
    }

    Personagem *campanha = (Personagem *)malloc(n * sizeof(Personagem));
    if (campanha == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    printf("\n--- Cadastro dos Personagens (%d no total) ---\n", n);
    for (i = 0; i < n; i++) {
        printf("\nPersonagem %d:\n", i + 1);
        printf(" ID (inteiro unico): ");
        scanf("%d", &campanha[i].id);
        
        printf(" Nome (uma palavra): ");
        scanf("%s", campanha[i].nome);
        
        printf(" Forca, Agilidade, Inteligencia (x y z): ");
        scanf("%d %d %d", 
              &campanha[i].forca, 
              &campanha[i].agilidade, 
              &campanha[i].inteligencia);
    }

    do {
        printf("\n=========================================\n");
        printf("Menu:\n");
        printf("1 - Consultar Personagem por ID\n");
        printf("2 - Sair\n");
        printf("Escolha a opcao: ");
        
        if (scanf("%d", &opcao) != 1) {

            while(getchar() != '\n'); 
            opcao = 0;
            continue;
        }

        if (opcao == 1) {
            int id_busca;
            int indice_encontrado;
            
            printf("Digite o ID do personagem que deseja consultar: ");
            if (scanf("%d", &id_busca) != 1) {
                while(getchar() != '\n'); 
                continue;
            }

            indice_encontrado = buscar_personagem(campanha, n, id_busca);

            if (indice_encontrado != -1) {
                Personagem p = campanha[indice_encontrado];

                float media = (float)(p.forca + p.agilidade + p.inteligencia) / 3.0f;
                
                printf("\n--- Personagem Encontrado ---\n");
                printf("Nome: %s\n", p.nome);
                printf("Forca: %d, Agilidade: %d, Inteligencia: %d\n", p.forca, p.agilidade, p.inteligencia);
                printf("Media de Atributos: %.2f\n", media);
            } else {
                printf("\nERRO: Personagem com ID %d nao existe na campanha.\n", id_busca);
            }
        }

    } while (opcao != 2);

    printf("\nEncerrando a ferramenta de consulta. Bom jogo!\n");
    free(campanha);
    campanha = NULL;

    return 0;
}

int buscar_personagem(const Personagem *personagens, int total, int id_busca) {
    for (int i = 0; i < total; i++) {
        if (personagens[i].id == id_busca) {
            return i; 
        }
    }
    
    return -1; 
}