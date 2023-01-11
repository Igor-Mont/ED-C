#include <stdio.h>

int main() {
  char character, letter;

  printf("Read a char: ");
  scanf("%c ", &character);

  printf("Read another char: ");
  // letter = getchar();
  // letter = getc(stdin);
  letter = fgetc(stdin);

  printf("Char is: %c\n", character);
  printf("Letter is: %c\n", letter);

  return 0;
}