#include <stdio.h>

int main() {
  int y = 0;
  short int x = 32767;
  long long int z = 2147483647;
  long double d = 3.13131313131313;

  printf("Size in memory of an int: %d bytes\n", sizeof y);
  printf("Size in memory of a short int: %d bytes\n", sizeof x);
  printf("Size in memory of a long int: %d bytes\n", sizeof z);
  printf("Size in memory of an int: %d bytes\n", sizeof(int));
  printf("Size in memory of a float: %d bytes\n", sizeof(float));
  printf("Size in memory of a double: %d bytes\n", sizeof(double));
  printf("Size in memory of a long double: %d bytes\n", sizeof d);
  
  return 0;
}