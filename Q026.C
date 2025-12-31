#include <stdio.h>
#include<stdlib.h>

int main(){
    int tamanho_inicial = 3;
    int novo_tamanho = 2 * tamanho_inicial;
    int *mochila = (int *) malloc(tamanho_inicial * sizeof(int));
    
    printf("Digite os valores dos 3 primeiros itens encontrados\n");
    for (int i = 0;i < tamanho_inicial; i++){
        printf("Item %d: ", i + 1);
        scanf("%d", &mochila[i]);
    }
    printf("\nItens na mochila: \n");
    for (int i = 0; i < tamanho_inicial; i++){
        printf("%d\n", mochila[i]);
    }
    
    printf("\nParabéns, você encontrou o item de expansão!\n");
    printf("Expandindo a mochila...\n");
    
    mochila = (int *) realloc(mochila, novo_tamanho * sizeof(int));
    printf("Voce liberou mais %d espaços! Digite os valores dos novos itens: \n", tamanho_inicial);
    for(int i = 3; i < novo_tamanho; i++){
        printf("Item %d: ", i + 1);
        scanf("%d", &mochila[i]);
    }
    
    printf("\nSeus itens foram armazenados com sucesso!\n");
    printf("Mochila Completa: \n");
    for(int i = 0; i < novo_tamanho; i++){
        printf("Item %d: %d\n", i + 1, mochila[i]);
    }
     free(mochila);
     mochila = NULL;
    
    return 0;
}