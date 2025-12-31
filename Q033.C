#include <stdio.h>

struct Posicao {
    int X; 
    int Y;
};

void mover_personagem(struct Posicao *p, int movimento_x, int movimento_y) {
    p->X += movimento_x;
    p->Y += movimento_y; 
}

int main() {
    struct Posicao posicao_jogador;
    posicao_jogador.X = 0;
    posicao_jogador.Y = 0;
    struct Posicao *ponteiro_posicao = &posicao_jogador;

    printf("Posicao inicial do jogador: X = %d, Y = %d\n", posicao_jogador.X, posicao_jogador.Y);
           
    mover_personagem(ponteiro_posicao, 10, 5);
    
    printf("Posicao final do jogador: X = %d, Y = %d\n", posicao_jogador.X, posicao_jogador.Y);

    return 0;
}