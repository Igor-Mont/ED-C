#include <stdio.h>

int main() {
  int maximum_capacity;
  int floors;

  scanf("%d %d", &floors, &maximum_capacity);

  int peoples_in = 0;

  for(int i = 0; i < floors; i++) {
    int peopes_left;
    int peopes_entered;
    scanf("%d %d", &peopes_left, &peopes_entered);

    peoples_in += peopes_entered - peopes_left;

    if(peoples_in > maximum_capacity) {
      printf("S"); 
      return 0;
    }
  }

  printf("N");

  return 0;
}