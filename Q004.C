#include <stdio.h>

void aplicar_powerup_pontuacao_dupla(int *pontuacao_jogador){
    *pontuacao_jogador = 2 * (*pontuacao_jogador);
}

int main(){
    int pontuacao_jogador = 1500;
    printf("Pontuacao antes do Power-UP: %d\n", pontuacao_jogador);

    aplicar_powerup_pontuacao_dupla(&pontuacao_jogador);
    printf("Pontuaacao apos o Power-UP: %d\n", pontuacao_jogador);

    return 0;
}