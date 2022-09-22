#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define MAX_SIZE 10
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define swap(x, y) { x = x + y; y = x - y; x = x - y; }

int* random_arr(int size) {
  srand((unsigned)time(NULL));
  int* arr = calloc(size, sizeof(*arr));
  for (int i = 0; i < size; i++) {
    arr[i] = rand() % 1000 - 500;
  }
  return arr;
}

void sort(int* arr, int size) {
  for (int i = 1; i < size; i++) {
    int j = i - 1;
    int key = arr[i];
    while (j >= 0 && key < arr[j]) {
      arr[j+1] = arr[j];
      j = j - 1;
    }
    arr[j+1] = key;
  }
}

int main(int argc, char* argv[]) {
  int size = argc == 2 ? atoi(argv[1]) : MAX_SIZE;
  int* arr = random_arr(size);
  sort(arr, size);
  for (int i = 0; i < size; i++) {
    log("%d\n", arr[i]);
  }
  free(arr);
  return 0;
}

