#include <stdio.h>
#include <string.h>

int main() {
   char frase_inicio_luta[] = "Você nunca sairá daqui com vida!\n";
   char caixa_dialogo[100] = "(Silêncio)";
   
   printf("Chefe antes da luta: %s\n", caixa_dialogo);
   strcpy(caixa_dialogo, frase_inicio_luta);
   printf("Chefe diz: %s", frase_inicio_luta);
  
    return 0;
}