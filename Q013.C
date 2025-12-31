#include <stdio.h>
#include <string.h>

int main(){
    char palavra_secreta[] = "LUX";
    char tentativa_jogador[50];
    
    printf("Uma voz ancestral ecoa... 'Diga a palavra e passe':");
    scanf("%[^\n]s", tentativa_jogador);
    if(strcmp(palavra_secreta, tentativa_jogador)==0){
        printf("A porta magica se abre!");
    }
    else{
        printf("Nada acontece... Parece que a palavra esta incorreta.");
    }
    
    return 0;
}