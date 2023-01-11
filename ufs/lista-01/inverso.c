#include <stdio.h>

int main() {
  int length;

  scanf("%d", &length);

  int list[length];

  length--;

  for(int i = 0; i <= length; i++) {
    scanf("%d", &list[i]);
  }

  for(int i = length; i >= 0; i--) {
    if(i == 0) {
      printf("%d", list[i]);
      break;
    }
    printf("%d ", list[i]);
  }

  return 0;
}