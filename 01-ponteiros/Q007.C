#include <stdio.h>

void ler_cenario(int n, int *cenario){
    
    for(int i = 0; i < n; i++){
        printf("Digite o %d valor(0 ou 1)\n", i + 1);
        scanf("%d", cenario + i);
    }
}

int main(){
    int n;

    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &n);
    int cenario[n];

    ler_cenario(n, cenario);

    for(int i = 0; i < n; i++){
       if (*(cenario + i) == 1){   // acessa valor com ponteiro = "cenario[n]"
            *(cenario + i) = 2;    // altera valor com ponteiro
            break;
        }
    }
    printf("Cenário final: ");
    for(int i = 0; i < n; i++){
        printf("%d ", *(cenario + i));
    }
    return 0;
}