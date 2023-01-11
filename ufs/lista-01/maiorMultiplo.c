#include <stdio.h>

int main() {
  int num;
  int limit;

  scanf("%d", &num);
  scanf("%d", &limit);

  int max = 0;

  for(int i = 1; i <= limit; i++) {
    if(!(i % num)) {
      if(i > max) {
        max = i;
      }
    }
  }

  if(!max) {
    printf("sem multiplos menores que %d", limit);
    return 0;
  }

  printf("%d", max);

  return 0;
}