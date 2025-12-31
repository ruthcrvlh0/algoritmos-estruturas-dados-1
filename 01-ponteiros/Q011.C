#include <stdio.h>

int main(){
    int balas[2] = {30, 30};
    int granadas[2] = {5, 5};
    int foguetes[2] = {2, 2};

    int *inventarios[3];
    inventarios[0]  = balas;
    inventarios[1] = granadas;
    inventarios[2] = foguetes;

    printf("Inventario Inicial: \n");
    printf("Balas: %d\n Granadas : %d\n Foguetes: %d\n" *inventarios[0], *inventarios[1], *inventarios[2]);

    for(int i = 0; i < 3; i++){
        *inventarios[i] = *inventarios[i] - 1;
    }
    printf("\n");
    printf("Inventario apos o uso: \n");
    printf("Balas: %d\n Granadas : %d\n Foguetes: %d\n", *inventarios[0], *inventarios[1], *inventarios[2]);

    return 0;
}