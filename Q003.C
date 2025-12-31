#include <stdio.h>
int main(){
    float coordenada_x ;
    float *ponteiro_x;
    
    ponteiro_x = &coordenada_x;
    printf("Digite o valor da coordenada X: \n");
    scanf("%f", &coordenada_x);
    
    printf("Posicao do portal no eixo X: [%.2f]\n", coordenada_x);
    printf("Endereco do portal para teletransporte: [%p]\n", ponteiro_x);

    return 0;

}