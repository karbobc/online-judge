#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e5 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Quick sort.
 */
void sort(char* s, int l, int r) {
  if (l >= r) {
    return;
  }
  int i = l;
  int j = r;
  char pivot = s[l];
  while (i < j) {
    while (i < j && s[j] >= pivot) {
      j--;
    }
    s[i] = s[j];
    while (i < j && s[i] <= pivot) {
      i++;
    }
    s[j] = s[i];
  }
  s[i] = pivot;
  sort(s, l, i-1);
  sort(s, i+1, r);
}

void dfs(char* temp, char* s, bool* visited, char** arr, int *returnSize) {
  int n = strlen(s);
  int lenTemp = strlen(temp);
  if (n == lenTemp) {
    arr[*returnSize] = malloc((n+1) * sizeof(**arr));
    strcpy(arr[(*returnSize)++], temp);
    return;
  }
  for (int i = 0; i < n; i++) {
    if (visited[i] || (i > 0 && s[i] == s[i-1] && !visited[i-1])) {
      continue;
    }
    visited[i] = true;
    temp[lenTemp] = s[i];
    temp[++lenTemp] = '\0';
    dfs(temp, s, visited, arr, returnSize);
    temp[--lenTemp] = '\0';
    visited[i] = false;
  }
}

char** permutation(char* s, int* returnSize) {
  // initialize
  *returnSize = 0;
  int n = strlen(s);
  char* str = malloc((n+1) * sizeof(*str));
  str[0] = '\0';;
  strcpy(str, s);
  sort(str, 0, n-1);
  char* temp = malloc((n+1) * sizeof(*temp));
  temp[0] = '\0';
  char** arr = malloc(MAX_SIZE * sizeof(*arr));
  bool* visited = malloc(n * sizeof(*visited));
  memset(visited, false, n * sizeof(*visited));
  // DFS
  dfs(temp, str, visited, arr, returnSize);
  // free and return
  free(visited);
  visited = NULL;
  free(temp);
  temp = NULL;
  free(str);
  str = NULL;
  return arr;
}

int main() {
  // define
  int returnSize;
  char* s = malloc(MAX_SIZE * sizeof(*s));
  char** arr = NULL;
  // input
  scanf("%s", s);
  // output
  arr = permutation(s, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%s\n", arr[i]);
    free(arr[i]);
    arr[i] = NULL;
  }
  // free memory
  free(s);
  s = NULL;
  if (arr != NULL) {
    free(arr);
    arr = NULL;
  }
  return 0;
}

