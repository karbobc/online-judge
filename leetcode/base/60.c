#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

void dfs(char* temp, int n, int* k, bool* visited, char* ret) {
  int j = strlen(temp);
  if (n == j) {
    if (--(*k) == 0) {
      strcpy(ret, temp);
    }
    return;
  }
  for (int i = 0; i < n && *k > 0; i++) {
    if (visited[i]) continue;
    visited[i] = true;
    temp[j] = (i+1) + '0';
    temp[j+1] = '\0';
    dfs(temp, n, k, visited, ret);
    temp[j] = '\0';
    visited[i] = false;
  }
}

char* getPermutation(int n, int k) {
  char* s = malloc((1 << 4) * sizeof(*s));
  char* ret = malloc((1 << 4) * sizeof(*ret));
  ret[0] = '\0';
  char* temp = malloc((1 << 4) * sizeof(*s));
  temp[0] = '\0';
  bool* visited = malloc(n * sizeof(*visited));
  memset(visited, false, n * sizeof(*visited));
  dfs(temp, n, &k, visited, ret);
  free(s);
  free(temp);
  free(visited);
  return ret;
}

int main() {
  int n, k;
  char* s = NULL;
  scanf("%d %d", &n, &k);
  s = getPermutation(n, k);
  log("%s\n", s);
  free(s);
  return 0;
}

