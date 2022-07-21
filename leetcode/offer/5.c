#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SRC_CHAR ' '
#define DES_CHAR "%20"
#define MAX_SIZE 1e4 + 4
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Given a string `s`, replace the space to `%20`.
 */
char* replaceSpace(char* s) {
  // define
  int sLen = strlen(s);
  int desLen = strlen(DES_CHAR);
  char* ret = malloc((sLen * desLen + 1) * sizeof(*ret));
  int j = 0;
  // replace
  for (int i = 0; i < sLen; i++) {
    if (s[i] == SRC_CHAR) {
      for (int k = 0; k < desLen; k++) {
        ret[j++] = DES_CHAR[k];
      }
      continue;
    }
    ret[j++] = s[i];
  }
  ret[j] = '\0';
  return ret;
}

int main() {
  // define
  char* ret = NULL;
  char* s = malloc(MAX_SIZE * sizeof(*s));
  // input
  scanf("%[^\n]", s);
  // fgets(s, MAX_SIZE, stdin);
  // s[strlen(s)-1] = '\0';
  // output
  ret = replaceSpace(s);
  log("%s\n", ret);
  // free memory
  if (ret != NULL) {
    free(ret);
    ret = NULL;
  }
  free(s);
  s = NULL;
  return 0;
}
