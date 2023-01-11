#include <stdio.h>

int main() {
  int seconds;
  unsigned short int minutes, hours, rest;

  printf("Type the number of seconds: ");
  scanf("%d", &seconds);

  hours = seconds / 3600;
  rest = seconds % 3600;
  minutes = rest / 60;
  seconds = rest % 60;

  printf("Hours: %d\n", hours); 
  printf("Minutes: %d\n", minutes); 
  printf("Seconds: %d", seconds); 

  return 0;
}