#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

void dfs(char* s, int i, char* digits, char** ans, int* returnSize) {
  int n = strlen(digits);
  if (n == 0) return;
  if (i == n) {
    ans[(*returnSize)] = malloc((n + 1) * sizeof(**ans));
    strcpy(ans[(*returnSize)++], s);
    return;
  }
  int digit = digits[i] - '0';
  for (int j = 0; j < (digit == 7 || digit == 9 ? 4 : 3); j++) {
    s[i] = 'a' + j + (digit - 2) * 3;
    s[i] += digit >= 8 ? 1 : 0;
    s[i+1] = '\0';
    dfs(s, i+1, digits, ans, returnSize);
    s[i] = '\0';
  }
}

char** letterCombinations(char* digits, int* returnSize) {
  *returnSize = 0;
  int n = strlen(digits);
  char** ans = malloc(MAX_SIZE * sizeof(*ans));
  char* s = malloc((n + 1) * sizeof(*s));
  dfs(s, 0, digits, ans, returnSize);
  free(s);
  return ans;
}

int main() {
  int returnSize;
  char** ans = NULL;
  char* digits = malloc(MAX_SIZE * sizeof(*digits));
  fgets(digits, MAX_SIZE, stdin);
  digits[strlen(digits)-1] = '\0';
  ans = letterCombinations(digits, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%s ", ans[i]);
  }
  log("\n");
  free(digits);
  if (ans != NULL) {
    for (int i = 0; i < returnSize; i++) {
      free(ans[i]);
    }
    free(ans);
  }
  return 0;
}

