#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int climbStairs(int n) {
  int dp[3] = {1, 2, 0};
  if (n < 3) {
    return dp[n-1];
  }
  for (int i = 2; i < n; i++) {
    dp[2] = dp[0] + dp[1];
    dp[0] = dp[1];
    dp[1] = dp[2];
  }
  return dp[2];
}

int main() {
  int n;
  scanf("%d", &n);
  log("%d\n", climbStairs(n));
  return 0;
}

