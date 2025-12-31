#include <stdio.h>
#include <stdlib.h>

struct Conquista {
    int id;
    int pontos;
};

int main() {
    FILE *arquivo = NULL;
    int N; 
    int total_experiencia = 0;
    struct Conquista conquista_atual;

    printf("--- Analise de Log de Conquistas ---\n");

    arquivo = fopen("player_log.txt", "r+");

    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo player_log.txt.\n");
        return 1;
    }

    if (fscanf(arquivo, "%d", &N) != 1) {
        printf("Erro: Falha ao ler o numero N de conquistas.\n");
        fclose(arquivo);
        return 1;
    }
    printf("Numero de conquistas a serem lidas: %d\n", N);

    for (int i = 0; i < N; i++) {
        if (fscanf(arquivo, "%d %d", &conquista_atual.id, &conquista_atual.pontos) == 2) {
            total_experiencia += conquista_atual.pontos;
        } else {
            printf("Aviso: Formato incorreto na linha %d. Interrompendo leitura.\n", i + 2);
            break;
        }
    }

    printf("Total de pontos de experiencia ganhos na sessao: %d\n", total_experiencia);
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        printf("Erro ao mover o ponteiro para o final do arquivo.\n");
        fclose(arquivo);
        return 1;
    }

    fprintf(arquivo, "\n--- SESSION CONCLUDED ---\n");
    printf("Marcador 'Sessao Concluida' adicionado ao arquivo.\n");
    fclose(arquivo);

    return 0;
}