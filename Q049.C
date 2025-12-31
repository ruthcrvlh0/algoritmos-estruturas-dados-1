#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo = NULL;
    const char *nome_arquivo = "level_1_map.dat";

    printf("--- Simulacao de Carregamento de Mapa ---\n");

    arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {

        printf("ERRO CRITICO: Nao foi possivel carregar os dados do mapa.\n");

        perror("Detalhes do erro");
   
        exit(1); 
    }
    printf("Mapa carregado com sucesso!\n");
    fclose(arquivo);
    
    return 0;
}