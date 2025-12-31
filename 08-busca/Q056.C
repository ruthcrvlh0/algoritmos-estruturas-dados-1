#include <stdio.h>

/**
 * @brief Calcula o dano total do Ataque em Cascata de forma recursiva.
 * * O dano no nivel N é igual a N + o dano do nivel N-1.
 * @param nivel O nivel atual do mago.
 * @return O dano total acumulado.
 */
int calcular_dano_cascata(int nivel) {
    if (nivel <= 1) {
        return 1;
    }

    return nivel + calcular_dano_cascata(nivel - 1);
}

int main() {
    int nivel_mago;
    int dano_final;

    printf("--- Calculo de Dano do Ataque em Cascata ---\n");
    printf("Digite o nivel do mago: ");
    
    if (scanf("%d", &nivel_mago) != 1 || nivel_mago <= 0) {
        printf("Nivel invalido. Digite um numero inteiro positivo.\n");
        return 1;
    }

    dano_final = calcular_dano_cascata(nivel_mago);
    printf("\nO dano total do Ataque em Cascata no nivel %d e: %d\n", nivel_mago, dano_final);

    return 0;
}