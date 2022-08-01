#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 32
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef unsigned int uint;

/**
 * Given a unsigned integer, return the count of number 1.
 */
int hammingWeight(uint n) {
  int cnt = 0;
  // T = O(log n)
  // while (n > 0) {
  //   cnt += (n & 1);
  //   n >>= 1;
  // }

  // T = O(m), m=count(1)
  while (n > 0) {
    cnt++;
    // clears the lowest bit of 1.
    n = n & (n-1);
  }
  return cnt;
}

uint btoi(char* s) {
  int len = strlen(s);
  uint ret = 0;
  for (int i = 0; i < len; i++) {
    ret += (s[len-i-1] - '0') * (1 << i);
  }
  return ret;
}

int main() {
  // define
  char* s = malloc((MAX_SIZE + 1) * sizeof(*s));
  // input
  scanf("%s", s);
  // output
  log("%d\n", hammingWeight(btoi(s)));
  // free memory
  free(s);
  s = NULL;
  return 0;
}

