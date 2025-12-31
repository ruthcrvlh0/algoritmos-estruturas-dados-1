#include <stdio.h>

int main() {
  int moedas_coletadas[] = {10, 50, 20, 5, 100};
  int pontuacao_total = 0;
  int *ponteiro_moeda;
  ponteiro_moeda = &moedas_coletadas[0];
  
  int *fim = moedas_coletadas +5; 
 
  while(ponteiro_moeda < fim){
     pontuacao_total += *ponteiro_moeda;
     ponteiro_moeda++;
  }
  
    printf ("Pontuação total do nível: %d \n", pontuacao_total);
  
    return 0;
}