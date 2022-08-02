#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e2 + 2)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * DFS find the exist path.
 */
bool dfs(char** board, int m, int n, char* word, bool** visited, int i, int j, int k) {
  if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] != word[k]) {
    return false;
  }
  if (k == strlen(word)-1) {
    return true;
  }
  visited[i][j] = true;
  bool ret = dfs(board, m, n, word, visited, i-1, j, k+1)
             || dfs(board, m, n, word, visited, i+1, j, k+1)
             || dfs(board, m, n, word, visited, i, j-1, k+1)
             || dfs(board, m, n, word, visited, i, j+1, k+1);
  visited[i][j] = false;
  return ret;
}

/**
 * Given a `m x n` array `board` and a string `word`,
 * true is returned when the `word` in the `board`.
 */
bool exist(char** board, int m, int* n, char* word) {
  // create an array `visited`
  bool** visited = malloc(m * sizeof(*visited));
  for (int i = 0; i < m; i++) {
    visited[i] = malloc((*n) * sizeof(**visited));
    memset(visited[i], false, (*n) * sizeof(**visited));
  }
  // find the path
  bool ret = false;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < *n && !ret; j++) {
      if (dfs(board, m, *n, word, visited, i, j, 0)) {
        ret = true;
      }
    }
  }
  // free memory
  for (int i = 0; i < m; i++) {
    free(visited[i]);
    visited[i] = NULL;
  }
  free(visited);
  visited = NULL;
  return ret;
}

int main() {
  // define
  int m, n;
  char* word = malloc(MAX_SIZE * sizeof(*word));
  char** board = malloc(MAX_SIZE * sizeof(*board));
  // input
  scanf("%d %d", &m, &n);
  scanf("%s", word);
  getchar();
  for (int i = 0; i < m; i++) {
    board[i] = malloc((n + 1) * sizeof(**board));
    scanf("%s", board[i]);
  }
  // output
  log(exist(board, m, &n, word) ? "true\n" : "false\n");
  // free memory
  for (int i = 0; i < m; i++) {
    free(board[i]);
    board[i] = NULL;
  }
  free(board);
  board = NULL;
  free(word);
  word = NULL;
  return 0;
}

