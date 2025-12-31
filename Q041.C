#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int opcao;
    char evento[100];
    FILE *log_arquivo = NULL;

    printf("--- Sistema de Log de Eventos ---\n");

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Registrar novo evento\n");
        printf("2 - Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1:
                log_arquivo = fopen("game_log.txt", "a");

                if (log_arquivo == NULL) {
                    printf("Erro: Nao foi possivel abrir o arquivo game_log.txt.\n");
                    break;
                }

                printf("Digite o evento (sem espacos): ");
                scanf("%s", evento);
                fprintf(log_arquivo, "%s\n", evento);
                fclose(log_arquivo);
                
                printf("Evento registrado com sucesso!\n");
                break;

            case 2:
                printf("Saindo do sistema de log. Conteudo salvo em game_log.txt.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 2);

    return 0;
}