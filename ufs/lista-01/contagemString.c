#include <stdio.h>
#include <string.h>

int main() {
  char frase[50];
  int quantidade = 0;
  fgets(frase, 50, stdin); // para de capturar no \n

  for(int i = 0; i < strlen(frase); i++) {
    if(frase[i] == 'a' || frase[i] == 'A') {
      quantidade++;
    }
  }

  printf("%d", quantidade);

  return 0;
}