#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e5 + 5)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define min(a, b) (a <= b ? a : b)
#define max(a, b) (a >= b ? a : b)

int maxArea(int* height, int n) {
  int ans = 0;
  int l = 0;
  int r = n - 1;
  while (l < r) {
    int h = min(height[l], height[r]);
    ans = max(ans, h * (r-l));
    height[l] > height[r] ? r-- : l++;
  }
  return ans;
}

int main() {
  int n;
  int* height = malloc(MAX_SIZE * sizeof(*height));
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &height[i]);
  }
  log("%d\n", maxArea(height, n));
  free(height);
  return 0;
}

