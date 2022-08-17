#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a > b ? a : b)

int longestCommonSubsequence(char* s1, char* s2) {
  int ret = 0;
  int m = strlen(s1);
  int n = strlen(s2);
  int** dp = malloc((m + 1) * sizeof(*dp));
  for (int i = 0; i <= m; i++) {
    dp[i] = malloc((n + 1) * sizeof(**dp));
  }
  for (int i = 0; i <= m; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= n; i++) {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i-1] == s2[j-1]) {
        dp[i][j] = 1 + dp[i-1][j-1];
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  ret = dp[m][n];
  for (int i = 0; i <= m; i++) {
    free(dp[i]);
  }
  free(dp);
  return ret;
}

int main() {
  // define
  char* s1 = malloc(MAX_SIZE * sizeof(*s1));
  char* s2 = malloc(MAX_SIZE * sizeof(*s2));
  // input
  fgets(s1, MAX_SIZE, stdin);
  s1[strlen(s1)-1] = '\0';
  fgets(s2, MAX_SIZE, stdin);
  s2[strlen(s2)-1] = '\0';
  // output
  log("%d\n", longestCommonSubsequence(s1, s2));
  // free memory
  free(s1);
  free(s2);
  return 0;
}

