#include <stdio.h>

int main() {
  int a, b, c;
  printf("Type two values: ");
  scanf("%d%d", &a, &b);

  c = a;
  a = b;
  b = c;

  printf("Value of a: %d\n", a);
  printf("Value of b: %d\n", b);

  return 0;
}