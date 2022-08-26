#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int mySqrt(int x) {
  if (x == 1) return x;
  int ret = 0;
  int l = 0;
  int r = x - 1;
  while (l <= r) {
    long mid = (l + r) >> 1;
    if (mid*mid <= x) {
      ret = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return ret;
}

int main() {
  int x;
  scanf("%d", &x);
  log("%d\n", mySqrt(x));
  return 0;
}

