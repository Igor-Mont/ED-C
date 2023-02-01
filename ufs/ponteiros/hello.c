#include <stdio.h>

// NÃO CHEGAMOS NO MÁXIMO DE 64 BITS DO HARDWARE COMERCIAL

// caso apareça endereços negativos, é pq o binário do endereõ começa com "1", e o print interpreta como nu  negativo
// memoria para drivers e etc acontece na parte alta da memoria 1111....
// memoria para apps e etc acontece na parte baixa da memoria 0000....

// #DEFINE É UM PRE PROCESSAMENTO 
void f2(char hello[]) {
  printf("from f2: %d\n", &hello);
}

void f1(char hello[]) {
  printf("from f1: %d\n", &hello);
  f2(hello);
}

void main() {

  char hello[] = "Hello World";
  printf("from main: %d\n", &hello);
  f1(hello);

  return;
}