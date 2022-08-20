#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int mySqrt(int x) {
  int ret = 0;
  for (long i = 0;;i++) {
    if (i*i == x) {
      ret = i;
      break;
    }
    if (i*i > x) {
      ret = i-1;
      break;
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

