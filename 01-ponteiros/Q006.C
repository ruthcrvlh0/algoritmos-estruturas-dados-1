#include <stdio.h>
int main (){
    int plataformas[] = {10, 20, 5, 15, 30};
    int *ponteiro_plataformas = plataformas;
    int altura_total = 0;
    
    int tamanho = sizeof(plataformas) / sizeof(plataformas[0]);
    
    for(int i = 0; i < tamanho; i++){
        altura_total += *(plataformas + i);
    }
    printf("Altura total do salto: %d metros!\n", altura_total);
    return 0;
}