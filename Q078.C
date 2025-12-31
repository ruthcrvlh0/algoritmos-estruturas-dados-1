//gcc Q078.c combate.c -o jogo
//./jogo

#include <stdio.h>
#include "combate.h" 

int main() {
    int ataque_base, bonus_espada, vida_inimigo_inicial;
    int dano_total_heroi;
    int vida_inimigo_final;

    printf("--- Modulo de Calculos de Combate RPG ---\n");

    printf("Digite o ataque base do heroi: ");
    if (scanf("%d", &ataque_base) != 1 || ataque_base < 0) return 1;

    printf("Digite o bonus da sua espada: ");
    if (scanf("%d", &bonus_espada) != 1 || bonus_espada < 0) return 1;

    printf("Digite a vida inicial do inimigo: ");
    if (scanf("%d", &vida_inimigo_inicial) != 1 || vida_inimigo_inicial < 0) return 1;

    dano_total_heroi = calcular_ataque_total(ataque_base, bonus_espada);
    vida_inimigo_final = aplicar_dano(vida_inimigo_inicial, dano_total_heroi);

    printf("\n--- Relatorio de Combate ---\n");
    printf("Poder de Ataque Total do Heroi: %d pontos\n", dano_total_heroi);
    printf("Dano Causado: %d pontos\n", dano_total_heroi);
    printf("Vida Inicial do Inimigo: %d\n", vida_inimigo_inicial);
    printf("Vida Restante do Inimigo: %d\n", vida_inimigo_final);
    
    if (vida_inimigo_final <= 0) {
        printf("Resultado: Inimigo Derrotado!\n");
    }

    return 0;
}