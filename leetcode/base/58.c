#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int lengthOfLastWord(char* s) {
  int n = strlen(s);
  int r = n - 1;
  int cnt = 0;
  for (int i = 0; i < n && s[n-i-1] == ' '; i++, r--);
  for (int i = 0; i <= r && s[r-i] != ' '; i++, cnt++);
  return cnt;
}

int main() {
  char* s = malloc(MAX_SIZE * sizeof(*s));
  fgets(s, MAX_SIZE, stdin);
  s[strlen(s)-1] = '\0';
  log("%d\n", lengthOfLastWord(s));
  free(s);
  return 0;
}

