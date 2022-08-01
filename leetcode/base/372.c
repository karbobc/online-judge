#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1337
#define MAX_SIZE (2e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Fast power algorithm.
 */
int fastpow(int x, int n, int mod) {
  int ret = 1;
  x = x % mod;
  while (n > 0) {
    if (n & 1) {
      ret = (ret * x) % mod;
    }
    x = (x * x) % mod;
    n >>= 1;
  }
  return ret;
}

/**
 * Given a integer `a` and an array `b`,
 * calculate a^b mod 1337.
 */
int superPow(int a, int* b, int bSize) {
  int ret = 1;
  int x = a % MOD;
  int n = bSize;
  // a^1234 = a^((10^0)*4) * a^((10^1)*3) * a^((10^2)*2) * a^((10^3)*1)
  //        = a^(1*4) * a^(10*3) * a^(100*2) * a^(1000*1)
  for (int i = 0; i < bSize; i++) {
    ret = (ret * fastpow(x, b[n-i-1], MOD)) % MOD;
    x = fastpow(x, 10, MOD);
  }
  return ret;
}

int main() {
  // define
  int a;
  int bSize;
  int* b = malloc(MAX_SIZE *sizeof(*b));
  // input
  scanf("%d %d", &a, &bSize);
  for (int i = 0; i < bSize; i++) {
    scanf("%d", &b[i]);
  }
  // output
  log("%d\n", superPow(a, b, bSize));
  // free memory
  free(b);
  b = NULL;
  return 0;
}

