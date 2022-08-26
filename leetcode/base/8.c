#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int myAtoi(char* s) {
  int l = 0;
  long ret = 0;
  bool negative = false;
  int n = strlen(s);
  while (l < n && s[l] == ' ') {
    l++;
  }
  if (l == n) return ret;
  if (s[l] == '-' || s[l] == '+') {
    negative = s[l] == '-';
    l++;
  }
  for (int i = l; i < n && s[i] >= '0' && s[i] <= '9'; i++) {
    ret = ret * 10 + s[i] - '0';
    if (negative && -ret < INT_MIN) {
      return INT_MIN;
    }
    if (!negative && ret > INT_MAX) {
      return INT_MAX;
    }
  }
  ret = negative ? -ret : ret;
  return (int) ret;
}

int main() {
  char* s = malloc(MAX_SIZE * sizeof(*s));
  fgets(s, MAX_SIZE, stdin);
  s[strlen(s)-1] = '\0';
  log("%d\n", myAtoi(s));
  free(s);
  return 0;
}

