#include <stdio.h>

int main() {
  int length;
  scanf("%d", &length);

  int nums[length];
  int lower = 0;
  int position = 0;

  for(int i = 0; i < length; i++) {
    scanf("%d", &nums[i]);
    if(nums[i] < lower) {
      lower = nums[i];
      position = i;
    }
  }

  printf("Menor valor: %d\n", lower);
  printf("Posicao: %d", position);

  return 0;
}