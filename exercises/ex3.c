#include <stdio.h>

int main() {
  int a, b;
  printf("Type two values: ");
  scanf("%d%d", &a, &b);

  a += b;
  b = a - b;
  a -= b;

  printf("Value of a: %d\n", a);
  printf("Value of b: %d\n", b);

  return 0;
}