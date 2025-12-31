#include <stdio.h>
int main(){
    int pontuacao = 0;
    int *ponteiro_pontuacao;
    ponteiro_pontuacao = &pontuacao;

    printf("Pontuacao inicial: %d\n", pontuacao);

    for(int i = 0; i < 3; i++){
        *ponteiro_pontuacao += + 10;
        printf("Pontuação após coletar 1 moeda: %d\n", *ponteiro_pontuacao);
    }
    printf("Pontuacao final apos coletar 3 moedas: %d\n", pontuacao);
    
    return 0;

}