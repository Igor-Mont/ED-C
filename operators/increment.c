#include <stdio.h>

int main() {

  int result, count = 10;

  result = count++;

  printf("Valor do resultado: %d\n", result);
  printf("Valor: %d\n", count);
  printf("Valor: %d\n", count++);
  printf("Valor: %d\n", ++count);

  return 0;
}