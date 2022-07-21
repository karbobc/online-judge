#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define SEGMENT_COUNT 4
#define MAX_SIZE 1e2 + 2
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)


void dfs(int start, int segId, const char* s, char** arr, int* segments, int* returnSize) {
  int len = strlen(s);
  if (segId == SEGMENT_COUNT) {
    if (start != len) {
      return;
    }
    // transform ip segment to ip address
    char* ip = (char*) calloc((len + SEGMENT_COUNT + 1), sizeof(char));
    char* buf = (char*) malloc(MAX_SIZE * sizeof(char));
    for (int i = 0; i < SEGMENT_COUNT; i++) {
      snprintf(buf, MAX_SIZE+1, i == 0 ? "%d" : ".%d", segments[i]);
      strcat(ip, buf);
    }
    // copy ip address into a string array
    arr[*returnSize] = (char*) malloc((len + SEGMENT_COUNT + 1) * sizeof(char));
    strcpy(arr[(*returnSize)++], ip);
    // free memory
    free(ip);
    free(buf);
    return;
  }
  // It'll be returning when the `segId` does not equal `SEGMENT_COUNT`,
  // and the position of start reaches the end of the string.
  if (start == len) {
    return;
  }
  // since there can be no leading 0,
  // if the current char is '0', 
  // then this segment of ip address can only be 0.
  if (s[start] == '0') {
    segments[segId] = 0;
    dfs(start+1, segId+1, s, arr, segments, returnSize);
    return;
  }
  // recursive all the possibility
  for (int i = start, segment = 0; i < len; i++) {
    segment = (segment * 10) + (s[i] - '0');
    if (segment <= 0 || segment > 255) {
      break;
    }
    segments[segId] = segment;
    dfs(i+1, segId+1, s, arr, segments, returnSize);
  }
}

/**
 * Given a string s containing only digits,
 * return all possible valid IP address.
 */
char** restoreIpAddresses(const char* s, int* returnSize) {
  char** arr = (char**) malloc(MAX_SIZE * sizeof(char*));
  int* segments = (int*) malloc(SEGMENT_COUNT * sizeof(int));
  *returnSize = 0;
  dfs(0, 0, s, arr, segments, returnSize);
  free(segments);
  return arr;
}

int main() {
  // define
  int returnSize;
  char** arr = NULL;
  char* s = (char*) malloc(MAX_SIZE * sizeof(char));
  // input
  scanf("%s", s);
  // output
  arr = restoreIpAddresses(s, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%s\n", arr[i]);
    free(arr[i]);
  }
  // free memory
  free(s);
  free(arr);
  return 0;
}

