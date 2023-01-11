#include <stdio.h>

int main() {
  int n1, n2, n3;

  printf("Digite tres valores: ");
  // it works through spaces ir enter
  scanf("%d%d%d", &n1, &n2, &n3);

  printf("Read values: %d, %d and %d", n1, n2, n3);

  return 0;
}