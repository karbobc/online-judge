#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "uthash.h"

#define MAX_SIZE (4e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct HashMap {
  char key;
  bool value;
  UT_hash_handle hh;
} HashMap, MapItem;

int lengthOfLongestSubstring(char* s) {
  int n = strlen(s);
  HashMap* map = NULL;
  MapItem* item = NULL;
  int l = 0, ret = 0;
  for (int i = 0; i < n; i++) {
    HASH_FIND(hh, map, &s[i], sizeof(*s), item);
    if (item == NULL) {
      item = malloc(sizeof(*item));
      item->key = s[i];
      HASH_ADD(hh, map, key, sizeof(*s), item);
      ret = i-l+1 > ret ? i-l+1 : ret;
      continue;
    }
    while (s[l] != s[i]) {
      HASH_FIND(hh, map, &s[l], sizeof(*s), item);
      HASH_DEL(map, item);
      free(item);
      item = NULL;
      l++;
    }
    l++;
  }
  // delete all the item
  MapItem* temp = NULL;
  HASH_ITER(hh, map, item, temp) {
    HASH_DEL(map, item);
    free(item);
    item = NULL;
  }
  return ret;
}

int main() {
  char* s = malloc(MAX_SIZE * sizeof(*s));
  scanf("%s", s);
  log("%d\n", lengthOfLongestSubstring(s));
  free(s);
  s = NULL;
  return 0;
}

