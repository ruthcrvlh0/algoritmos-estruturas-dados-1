#include <stdio.h>
int main(){
    int vida_jogador = 100;
    int *ponteiro_vida;
    
    vida_jogador = 50;
    printf("O jogador sofreu dano! Vida atual: 50\n");
    ponteiro_vida = &vida_jogador;
    *ponteiro_vida = 100;
    printf("Power-up coletado! Vida restaurada: 100\n");
    
    return 0;

}