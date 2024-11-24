#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LIMIT 100

int* alloc(int size);
void input(int* list, int size);
void bucketSort(int* list, int size);
void display(int* list, int size);
void insertionSort(int* list, int size);

int main() {
    int* list, size;
    printf("Enter the size of list: ");
    scanf("%d", &size);
    if(size < 0 || size >= MAX_LIMIT){
        printf("Invalid limit. \n");
        return 1;
    }
    list = alloc(size);
    printf("Enter the elements: ");
    input(list, size);
    bucketSort(list, size);
    display(list, size);
    free(list);
    return 0;
}

int* alloc(int size){
    int* list = (int*)calloc(size, sizeof(int));
    return list;
}

void input(int* list, int size){
    for(int i = 0; i < size; i++)
        scanf("%d", &list[i]);
}

void insertionSort(int* list, int size){
    int j;
    for(int i = 1; i < size; i++){
        int key = list[i];
        j = i - 1;
        while(j >= 0 && list[j] > key){
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
    }
}

void bucketSort(int* list, int size) {
    // Create bucket array
    int bucketCount = sqrt(size);
    int** buckets = (int**)malloc(bucketCount * sizeof(int*));
    int* bucketSizes = (int*)malloc(bucketCount * sizeof(int));
    int i, j, k;

    // Initialize buckets
    for (i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(size * sizeof(int));
        bucketSizes[i] = 0;
    }

    // Determine the range
    int max = list[0], min = list[0];
    for (i = 1; i < size; i++) {
        if (list[i] > max) max = list[i];
        if (list[i] < min) min = list[i];
    }
    float range = (float)(max - min) / bucketCount;

    // Distribute elements into buckets
    for (i = 0; i < size; i++) {
        int bucketIndex = (int)((list[i] - min) / range);
        if (bucketIndex == bucketCount) {
            bucketIndex--;
        }
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = list[i];
    }

    // Sort each bucket and concatenate the result
    k = 0;
    for (i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i], bucketSizes[i]);
        for (j = 0; j < bucketSizes[i]; j++) {
            list[k++] = buckets[i][j];
        }
    }

    // Free allocated memory
    for (i = 0; i < bucketCount; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
}

void display(int* list, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}
