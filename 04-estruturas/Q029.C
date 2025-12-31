#include <stdio.h>

struct ItemColetavel { 
    int valor_pontos; 
    float peso;
}; 
    
int main() {
    int pontuacao_jogador = 0;
    
    struct ItemColetavel moeda_bronze = {10, 0.50};
    struct ItemColetavel moeda_prata = {50, 0.70};
    struct ItemColetavel moeda_ouro = {100, 1};
    
    pontuacao_jogador = pontuacao_jogador + moeda_ouro.valor_pontos;
    printf("Moeda de ouro coletada! Pontuação atual: %.d\n", pontuacao_jogador);
    
    return 0;
}