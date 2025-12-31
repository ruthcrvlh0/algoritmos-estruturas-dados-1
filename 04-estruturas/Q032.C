#include <stdio.h>

struct Personagem {
    int posX; 
    int posY; 
    int moedas;
};

struct Personagem atualizarPersonagem(struct Personagem p){
    p.posX = 10;
    p.posY = 5;
    p.moedas++;
    return p;
}

int main() {
    struct Personagem jogador;
    jogador.posX = 0;
    jogador.posY = 0;
    jogador.moedas = 0;
    
    printf( "Posicao inicial: (%d, %d) - Moedas: %d\n", jogador.posX, jogador.posY, jogador.moedas);
    
    jogador = atualizarPersonagem(jogador);
    printf("Posicao atualizada: (%d, %d) - Moedas: %d\n", jogador.posX, jogador.posY, jogador.moedas);
    
    return 0;
}