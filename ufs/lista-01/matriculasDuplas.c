#include <stdio.h>

int main() {
  int students_II[45];
  int students_III[30];

  int both_disciplines[30];

  for(int i = 0; i < 45; i++) {
    scanf("%d", &students_II[i]);
  }
  
  for(int i = 0; i < 30; i++) {
    scanf("%d", &students_III[i]);
  }

  int index = 0;

  for(int i = 0; i < 45; i++) {
    students_II[i];
    for(int ii = 0; ii < 30; ii++) {
      if(students_II[i] == students_III[ii]) {
        both_disciplines[index] = students_II[i];
        index++;
      }
    }
  }

  for(int i = 0; i < index; i++) {
    if(i == index - 1) {
      printf("%d \n", both_disciplines[i]);
      break;
    }

    printf("%d ", both_disciplines[i]);
  }

  return 0;
}