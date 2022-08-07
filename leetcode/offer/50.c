#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (5e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

char firstUniqChar(char* s) {
  char ret = ' ';
  int n = strlen(s);
  int* set = calloc((1 << 7), sizeof(*set));
  for (int i = 0; i < n; i++) {
    set[s[i]]++;
  }
  for (int i = 0; i < n; i++) {
    if (set[s[i]] == 1) {
      ret = s[i];
      break;
    }
  }
  free(set);
  set = NULL;
  return ret;
}

int main() {
  char* s = malloc(MAX_SIZE * sizeof(*s));
  fgets(s, MAX_SIZE, stdin);
  s[strlen(s)-1] = '\0';
  log("%c\n", firstUniqChar(s));
  free(s);
  s = NULL;
  return 0;
}

