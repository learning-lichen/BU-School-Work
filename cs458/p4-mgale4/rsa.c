#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void check_input(int argc, char** argv);
int calculate_e(int phi_n);
int calculate_d(int e, int n, int phi_n);
int gcd(int a, int b);

int main(int argc, char** argv) {
  int p;
  int q;
  int n;
  int phi_n;
  int e;
  int d;

  check_input(argc, argv);

  p = atoi(argv[1]);
  q = atoi(argv[2]);
  n = p * q;
  phi_n = (p - 1) * (q - 1);

  printf("n = %d\n", n);
  printf("phi(n) = %d\n", phi_n);

  e = calculate_e(phi_n);
  printf("e = %d\n", e);

  d = calculate_d(e, n, phi_n);
  printf("d = %d\n", d);

  return 0;
}

void check_input(int argc, char** argv) {
  int p;
  int q;

  if (argc != 3) {
    printf("Usage: ./rsa p q\n");
    exit(1);
  }

  p = atoi(argv[1]);
  q = atoi(argv[2]);

  if (p <= 0 || q <= 0) {
    printf("Both p and q must be positive integers.\n");
    exit(1);
  }
}

// The idea for calculating random numbers was taken from:
// http://www.cprogramming.com/tutorial/random.html
int calculate_e(int phi_n) {
  int e;
  time_t seconds;

  time(&seconds);
  srand((unsigned int) seconds);
  
  do {
    e = (rand() % (phi_n - 2)) + 2;
  } while (gcd(e, phi_n) != 1);

  return e;
}

int calculate_d(int e, int n, int phi_n) {
  int d = -1;
  int i;

  for (i = 0; i <= n && d < 0; ++i) {
    if ((e * i) % phi_n == 1)
      d = i;
  } 

  return d;
}

int gcd(int a, int b) {
  int min = a < b ? a : b;
  int gcd = 1;
  int i;

  for (i = 2; i <= min; ++i) {
    if (a % i == 0 && b % i == 0)
      gcd = i;
  }
  
  return gcd;
}
