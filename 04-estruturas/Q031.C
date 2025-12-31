#include <stdio.h>

typedef struct{
    int pontos;
    float pos_x;
    float pos_y; 
}Coletavel;

int main() {
    Coletavel gema_rara; 
    printf("Digite o valor em pontos, a posição X e a posição Y da gema_rara: ");
    scanf("%d %f %f", &gema_rara.pontos, &gema_rara.pos_x, &gema_rara.pos_y);
    
    printf("Coletável criado! Valor: [%d] pontos. Posição: (X=[%.1f], Y=[%.1f]", gema_rara.pontos, gema_rara.pos_x, gema_rara.pos_y);
    
    return 0;
}