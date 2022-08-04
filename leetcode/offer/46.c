#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1e2 + 2)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int translateNum(int num) {
  if (num < 10) {
    return 1;
  }
  int end = num % 100;
  if (end >= 10 && end <= 25) {
    return translateNum(num / 10) + translateNum(num / 100);
  }
  return translateNum(num / 10);
}

int main() {
  int num;
  scanf("%d", &num);
  log("%d\n", translateNum(num));
  return 0;
}

