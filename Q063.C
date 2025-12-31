#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PLACAR 5

int main() {
    int placar[TAMANHO_PLACAR] = {120, 125, 130, 142, 150};
    int novo_tempo;
    int i;
    int posicao_insercao = -1; 

    printf("--- Sistema de Leaderboard (Top 5) ---\n");
    printf("Placar atual: %d, %d, %d, %d, %d\n", 
           placar[0], placar[1], placar[2], placar[3], placar[4]);

    printf("\nDigite o novo tempo de corrida: ");
    if (scanf("%d", &novo_tempo) != 1) {
        printf("Entrada invalida. Encerrando.\n");
        return 1;
    }

    for (i = TAMANHO_PLACAR - 1; i >= 0; i--) {
        
        if (novo_tempo < placar[i]) {
            if (i < TAMANHO_PLACAR - 1) {
                placar[i + 1] = placar[i];
            }

            posicao_insercao = i;
            
        } else {
            if (posicao_insercao == -1 && i < TAMANHO_PLACAR - 1) {
                posicao_insercao = i + 1;
            }
            break; 
        }
    }
    
    if (posicao_insercao == -1 && novo_tempo < placar[0]) {
        posicao_insercao = 0;
    }

    if (posicao_insercao != -1 && posicao_insercao < TAMANHO_PLACAR) {
        placar[posicao_insercao] = novo_tempo;
        printf("\n[SUCESSO] Novo recorde inserido na posicao %d.\n", posicao_insercao + 1);
    } else {
        printf("\n[INFO] O tempo %d nao e um dos Top 5 recordes.\n", novo_tempo);
    }

    printf("\n--- Placar Final Ordenado ---\n");
    for (i = 0; i < TAMANHO_PLACAR; i++) {
        printf("%d ", placar[i]);
    }
    printf("\n");

    return 0;
}