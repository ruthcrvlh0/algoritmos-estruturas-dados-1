#include <stdio.h>
#include <stdlib.h>

struct Configuracao {
    int resolucao_x;
    int resolucao_y;
    float volume_som;
};

int main() {
    FILE *arquivo = NULL;
    struct Configuracao conf;

    printf("--- Carregamento de Arquivo de Configuracao ---\n");
    arquivo = fopen("config.txt", "r");

    if (arquivo == NULL) {
        printf("Erro: Arquivo config.txt nao encontrado!\n");
        return 1;
    }

    printf("Arquivo config.txt encontrado e aberto.\n");

    if (fscanf(arquivo, "%d %d %f", 
               &conf.resolucao_x, 
               &conf.resolucao_y, 
               &conf.volume_som) != 3) {
        
        printf("Erro: Falha ao ler todos os dados do arquivo.\n");
        fclose(arquivo);
        return 1;
    }

    printf("\nConfiguracoes carregadas:\n");
    printf("Resolucao: %dx%d\n", conf.resolucao_x, conf.resolucao_y);
    printf("Volume: %.1f\n", conf.volume_som);

    fclose(arquivo);

    return 0;
}