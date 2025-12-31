#include <stdio.h>

enum EstadoPersonagem {
    PARADO,
    CORRENDO,
    PULANDO
};

int main() {
    enum EstadoPersonagem estado_atual;
    int entrada_usuario;

    printf("--- Simulacao de Estados do Personagem ---\n");
    printf("Digite o numero do estado (0=PARADO, 1=CORRENDO, 2=PULANDO): ");
    
    scanf("%d", &entrada_usuario);
    estado_atual = entrada_usuario;

    if (estado_atual == PARADO) {
        printf("O personagem está parado.\n");
        
    } else if (estado_atual == CORRENDO) {
        printf("O personagem está correndo!\n");
        
    } else if (estado_atual == PULANDO) {
        printf("O personagem está pulando no ar!\n");
        
    } else {
        printf("Estado inválido!\n");
    }

    return 0;
}