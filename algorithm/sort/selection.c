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
        arr[i] = rand() % 1000 - 500;
    }
    return arr;
}

void sort(int* arr, int size) {
    for (int i = 0; i < size-1; i++) {
        int min = i;
        for (int j = i+1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(arr[i], arr[min]);
        }
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


