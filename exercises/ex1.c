#include <stdio.h>

int main() {
  char sex;
  int age;
  float weight, height;

  printf("Type sex, age, weight and height: ");
  scanf("%c%d%f%f", &sex, &age, &weight, &height);

  printf("Sex: %c\nAge: %d\nWeight: %.1f\nHeight: %.2f", sex, age, weight, height);

  return 0;
}