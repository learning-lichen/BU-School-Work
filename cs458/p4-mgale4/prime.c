#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void check_input(int argc, char** argv);
void primality_test(int n, int a);
int calculate_k(int n, int min);

int main(int argc, char** argv) {
  int n;
  int a;

  double ex = pow(5, 25);
  printf("%f\n", ex);

  check_input(argc, argv);

  n = atoi(argv[1]);
  a = atoi(argv[2]);

  // Handle the edge cases.
  if (n <= 3) 
    printf("%d is prime\n", n);
  else if (n % 2 == 0)
    printf("%d is a composite\n", n);
  else 
    primality_test(n, a);
  
  return 0;
}

void check_input(int argc, char** argv) {
  int n;
  int a;

  if (argc != 3) {
    perror("Usage: ./prime <n> <a>\n");
    exit(1);
  }

  n = atoi(argv[1]);
  a = atoi(argv[2]);

  if (n <= 0 || a <= 0) {
    perror("n and a must be positive integers.\n");
    exit(1);
  }
}

void primality_test(int n, int a) {
  int k;
  int q;
  int j;
  long exponent;

  k = calculate_k(n, 0);
  
  while (k >= 0) {
    q = n / pow(2, k);
    
    printf("k = %d\n", k);
    printf("q = %d\n", q);
    
    if (lround(pow(a, q)) % n == 1) {
      printf("%d may be prime\n", n);
      return;
    } else 
      printf("a^q mod n = %ld\n", lround(pow(a, q)) % n);
    
    for (j = 1; j <= k; ++j) {
      exponent = pow(2, (j - 1)) * q;
      
      if (lround(pow(a, exponent)) % n == n - 1) {
	printf("%d may be prime\n", n);
	return;
      } else
	printf("j = %d, a^(2^(j-1)*q) mod n = %ld\n", j, lround(pow(a, exponent)) % n);
    }

    k = calculate_k(n, k);
  }
  
  printf("%d is not prime\n", n);
}
int calculate_k(int n, int min) {
  int i = min;
  int k = -1;

  --n; // n is odd, so subtract by one so it is even.

  while(lround(pow(2, i)) <= n) {
    if (n % lround(pow(2, i)) == 0 && (n / lround(pow(2, i))) % 2 == 1) 
      k = i > min ? i : -1;
      
    ++i;
  }

  return k;
}
