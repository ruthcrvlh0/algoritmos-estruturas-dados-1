#include <stdio.h>
#include <string.h>

int main() {
    char inventario[5][20];
    char item_abrir_porta[20];
    int encontrou;
    
    printf("Digite o nome dos intens que estão no inventário: ");
    scanf("%19s %19s %19s %19s %19s", &inventario[0], &inventario[1], &inventario[2], &inventario[3], &inventario[4]);
    printf("Digite o nome do item necessário para abrir a porta: ");
    scanf("%s", item_abrir_porta);
   for(int i = 0; i< 5; i++){
       strcmp(item_abrir_porta, inventario[i]);
       if(strcmp(item_abrir_porta, inventario[i]) == 0){
           encontrou = 1;
       }
    }
    
   if (encontrou >= 1){
       printf("Porta aberta!");
   }
    else{
        printf("Você não tem o item necessário.");
    }
    
    return 0;
}