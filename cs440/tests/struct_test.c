#include <stdio.h>

int main() {
  struct C {
    char b;
  };

  printf("%lu\n", sizeof(struct C));

  return 0;
}
