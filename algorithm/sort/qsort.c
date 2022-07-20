#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 10
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define swap(x, y) { x = x + y; y = x - y; x = x - y;}


int* random_arr(int size) {
    srand((unsigned) time(NULL));
    int* arr = (int *) calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        *(arr + i) = rand() % 1000 - 500;
    }
    return arr;
}

void sort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[left];
        int i = left;
        int j = right;
        while (i < j) {
            while (arr[j] >= pivot && i < j) {
                j--;
            }
            arr[i] = arr[j];
            while (arr[i] <= pivot && i < j) {
                i++;
            }
            arr[j] = arr[i];
        }
        arr[i] = pivot;
        sort(arr, left, i - 1);
        sort(arr, i + 1, right);
    }
}

int main(int argc, char* argv[]) {
    int size = argc == 2 ? atoi(argv[1]) : MAX_SIZE;
    int* arr = random_arr(size);
    sort(arr, 0, size - 1);
    for (int i = 0; i < size; i++) {
        log("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}

