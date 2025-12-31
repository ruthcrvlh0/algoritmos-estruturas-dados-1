#include <stdio.h>

int main() {
    float forca_base, bonus_arma, bonus_buff;
    float dano_total;

    printf("--- Calculo de Dano Final (RPG) ---\n");
 
    printf("Digite a forca base do personagem: ");
    scanf("%f", &forca_base);

    printf("Digite o bonus de dano da arma: ");
    scanf("%f", &bonus_arma);

    printf("Digite o bonus do feitico (buff): ");
    scanf("%f", &bonus_buff);

    dano_total = forca_base + bonus_arma + bonus_buff;

    printf("\n--- Resultado ---\n");
    printf("Dano Total Final: %.2f\n", dano_total);

    return 0;
}