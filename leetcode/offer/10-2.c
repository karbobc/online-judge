#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD ((int) 1e9 + 7)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##_VA_ARGS__)

int numWays(int n) {
  int dp[3] = {1, 1, 0};
  if (n < 2) {
    return dp[n];
  }
  for (int i = 2; i <= n; i++) {
    dp[2] = (dp[0] + dp[1]) % MOD;
    dp[0] = dp[1];
    dp[1] = dp[2];
  }
  return dp[2];
}

int main() {
  int n;
  scanf("%d", &n);
  log("%d\n", numWays(n));
  return 0;
}

