#include <stdlib.h>
#include <stdio.h>

int main() {
  int i;
  int j;
  int **a1 = (int **) malloc((20 * sizeof(int*)) + 600 * sizeof(int));
  for (i = 0; i < 20; ++i)
    a1[i] = (int*) (a1 + (20 * sizeof(int*))) + (i * 30 * sizeof(int));

  int (*a2)[30] = (int (*) [30]) malloc(sizeof(20 * sizeof(int [30])));

  for (i = 0; i < 20; ++i) {
    for (j = 0; j < 30; ++j) {
      a1[i][j] = i;
    }
  }

  for (i = 0; i < 20; ++i) {
    for (j = 0; j < 30; ++j) {
      printf("%d  ", a1[i][j]);
    }

    printf("\n");
  }
  
  free(a1);
  return 0;
}
