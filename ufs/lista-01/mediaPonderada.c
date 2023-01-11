#include <stdio.h>

char* AnalisarSituacao(float nota_1, float nota_2, float nota_3, float nota_4) {
  int peso_1 = 1;
  int peso_2 = 2;
  int peso_3 = 3;
  int peso_4 = 4;
  int soma_pesos = peso_1 + peso_2 + peso_3 + peso_4;

  float soma_nota_peso = (nota_1 * peso_1) + (nota_2 * peso_2) + (nota_3 * peso_3) + (nota_4 * peso_4);

  float media = soma_nota_peso / soma_pesos;

  if(media >= 9) return "aprovado com louvor";
  if(media >= 7) return "aprovado";
  if(media < 3) return "reprovado";
  
  return "prova final";
}

int main() {
  float nota_1;
  float nota_2;
  float nota_3;
  float nota_4;

  scanf("%f %f %f %f", &nota_1, &nota_2, &nota_3, &nota_4);

  printf("%s", AnalisarSituacao(nota_1, nota_2, nota_3, nota_4));

  return 0;
}