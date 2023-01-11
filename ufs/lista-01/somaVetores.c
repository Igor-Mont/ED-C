#include <stdio.h>

int main() {
  int vetor_1[10];
  int vetor_2[10];
  int vetor_soma[10];
  
  for(int i = 0; i < 10; i++) {
    scanf("%d", &vetor_1[i]);
  }

  for(int i = 0; i < 10; i++) {
    scanf("%d", &vetor_2[i]);
  }

  for(int i = 0; i < 10; i++) {
    vetor_soma[i] = vetor_1[i] + vetor_2[i];
  }

  for(int i = 0; i < 10; i++) {
    if(i == 9) {
      printf("%d", vetor_soma[i]);
      break;
    }
    printf("%d ", vetor_soma[i]);
  }

  return 0;
}