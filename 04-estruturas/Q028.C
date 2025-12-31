#include <stdio.h>

struct Jogador { 
    float pos_x;
    int pontuacao;
    int tem_pulo_duplo; 
}; 
    
int main() {
    
    struct Jogador heroi; 
    heroi.pos_x = 50.0f; 
    heroi.pontuacao = 0;
    heroi.tem_pulo_duplo = 0;

    printf("Inicio da fase!\n");
    printf("Posicao X: %.1f, Pontos: %d, Pulo Duplo: %s\n", 
           heroi.pos_x, heroi.pontuacao, heroi.tem_pulo_duplo == 1 ? "Sim" : "Nao");
    
    heroi.pontuacao += 10;
    heroi.tem_pulo_duplo = 1;
    
    printf("Voce coletou uma moeda e um Power-UP!\n");
    printf("Itens coletados! Posicao X: %.1f, Pontos: %d, Pulo Duplo: %s\n", 
           heroi.pos_x, heroi.pontuacao, heroi.tem_pulo_duplo == 1 ? "Sim" : "Nao");

    return 0;
}