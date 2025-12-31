#include <stdio.h>
#include "personagem.h" 

int main() {
    int num_membros;
    Personagem* equipe = NULL; 

    printf("--- Gerenciador de Equipes (TAD) ---\n");

    printf("Digite o numero de membros para a equipe (N): ");
    if (scanf("%d", &num_membros) != 1 || num_membros <= 0) {
        printf("Numero de membros invalido. Encerrando.\n");
        return 1;
    }

    equipe = cria_party(num_membros);
    if (equipe == NULL) {
        return 1;
    }

    registra_membros(equipe, num_membros);

    exibe_relatorio(equipe, num_membros);

    libera_party(equipe);
    
    return 0;
}