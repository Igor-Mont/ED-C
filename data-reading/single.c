#include <stdio.h>

int main() {
  int integer;
  float real;

  printf("Read an integer number: ");
  scanf("%d", &integer);

  printf("Read a real number: ");
  scanf("%f", &real);

  printf("Integer number is: %d\n", integer);
  printf("Real number is: %.2f\n", real);

  return 0;
}