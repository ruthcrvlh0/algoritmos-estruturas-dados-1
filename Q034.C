#include <stdio.h>

struct Heroi {
    int saude;
    int pontuacao;
    int posX;
    int posY;
}; 

int main() {
    struct Heroi meuHeroi;
    
    meuHeroi.saude = 100;
    meuHeroi.pontuacao = 0;
    meuHeroi.posX = 0;
    meuHeroi.posY = 0;
    
    printf("--- Estado Inicial ---\n");
    printf("Saude: %d | Pontuacao: %d | PosX: %d | PosY: %d\n\n", 
           meuHeroi.saude, meuHeroi.pontuacao, meuHeroi.posX, meuHeroi.posY);
    
    struct Heroi *ptrHeroi = &meuHeroi; 

    ptrHeroi->saude -= 25;
    printf("Acao: Sofreu dano. Nova Saude: %d\n", ptrHeroi->saude);
    
    ptrHeroi->pontuacao += 50;
    printf("Acao: Coletou moedas. Nova Pontuacao: %d\n", ptrHeroi->pontuacao);
    
    ptrHeroi->posX += 10;
    ptrHeroi->posY -= 5;
    printf("Acao: Heroi se moveu. Nova Posicao: (%d, %d)\n", ptrHeroi->posX, ptrHeroi->posY);
    
    printf("\n--- Estado Final Completo ---\n");
    printf("Saude: %d | Pontuacao: %d | PosX: %d | PosY: %d\n", ptrHeroi->saude, ptrHeroi->pontuacao, ptrHeroi->posX, ptrHeroi->posY);
    
    return 0;
}