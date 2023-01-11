#include <stdio.h>
#include <string.h>
#include <ctype.h>

void capturaValores(char* nome, int* pontuacao) {
  scanf("%s", nome);

  for(int i = 0; i < 3; i++) {
    scanf("%d", &pontuacao[i]);
  }
}

void transformaNomeParaLowerCase(char* nome) {
  for(int i = 0; i < strlen(nome); i++){
    nome[i] = tolower(nome[i]);
  }
}

int decideVencedor(int* time1, int* time2) {
  int vencedor = 0;

  for(int i = 0; i < 3; i++) {
    if(time1[i] > time2[i]){
      vencedor = 1;
      return vencedor;
    }

    if(time1[i] < time2[i]){
      vencedor = 2;
      return vencedor;
    }
  }

  return vencedor;
}

int main() {
  char nome_time_1[10];
  char nome_time_2[10];
  int pontuacao_time_1[3];
  int pontuacao_time_2[3];

  capturaValores(nome_time_1, pontuacao_time_1);
  capturaValores(nome_time_2, pontuacao_time_2);

  int vencedor = decideVencedor(pontuacao_time_1, pontuacao_time_2);

  if(vencedor == 0) {
    printf("EMPATE");
    return 0;
  }

  if(vencedor == 1) {
    transformaNomeParaLowerCase(nome_time_1);
    printf("%s", nome_time_1);
    return 0;
  }

  if(vencedor == 2) {
    transformaNomeParaLowerCase(nome_time_2);
    printf("%s", nome_time_2);
    return 0;
  }

  return 0;
}