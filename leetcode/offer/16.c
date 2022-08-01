#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Fast power algorithm.
 */
double myPow(double x, int n) {
  if (x == 0) {
    return 0;
  }
  long b = n;
  if (n < 0) {
    x = 1.0 / x;
    b = -n;
  }
  double ret = 1.0;
  while (b > 0) {
    if (b & 1) {
      ret *= x;
    }
    x *= x;
    b >>= 1;
  }
  return ret;
}

int main() {
  // define
  double x;
  int n;
  // input
  scanf("%lf %d", &x, &n);
  // output
  log("%.5f\n", myPow(x, n));
  return 0;
}

