#include <stdio.h>

int main() {
  unsigned int x = 2147483647;
  // 4 bytes * 8 bits = 31 bytes to store the number and 1 to sign
  // As the operator does not need a sign, 32 bits are left to store the number

  printf("\n\t%d\n\n", ++x);

  return 0;
}