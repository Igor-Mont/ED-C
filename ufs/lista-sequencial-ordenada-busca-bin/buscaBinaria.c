#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// pesquisar sobre a busca interpolada
// fazer a inserção na ordem na posição, o prof ja fez na ordem

bool buscaBinaria(int l[20], int size, int num) {
  int begin = 0;
  int end = size - 1;

  if(l[begin] == num) return true;
  if(l[end] == num) return true;

  while (begin <= end) { 
      int middle = (begin + end) / 2;

      if (l[middle] == num) return true;

      if (l[middle] < num)  
          begin = middle + 1;

      if (l[middle] > num)
          end = middle;
  }

  return false;
}

int main() {
  int vector[28] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

  double time_spent = 0.0;
  clock_t begin = clock();

  bool find = buscaBinaria(vector, 28, 28);

  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("The elapsed time is %f seconds\n", time_spent);

  printf(find ? "Find!": "Bad!");


  return 0;
}