#include <stdio.h>

int main() {
  float expense, tip, valuePerPerson;
  unsigned short int nPeoples;

  printf("Type an expense: ");
  scanf("%f", &expense);
  printf("Type a tip in percent: ");
  scanf("%f", &tip);
  printf("Type a number of peoples to split the bill: ");
  scanf("%d", &nPeoples);

  valuePerPerson = (expense + (expense * (tip / 100))) / nPeoples;

  printf("The value to each person is: %.2f", valuePerPerson);

  return 0;
}