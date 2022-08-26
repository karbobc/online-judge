#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define OUT_OF_RANGE 0
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int reverse(int x) {
  int ret = 0;
  if (x <= INT_MIN || x > INT_MAX) {
    return OUT_OF_RANGE;
  }
  while (x != 0) {
    if (ret > INT_MAX / 10 || ret < INT_MIN / 10) {
      return OUT_OF_RANGE;
    }
    ret = ret * 10 + x % 10;
    x /= 10;
  }
  return ret;
}

int main() {
  int x;
  scanf("%d", &x);
  log("%d\n", reverse(x));
  return 0;
}

