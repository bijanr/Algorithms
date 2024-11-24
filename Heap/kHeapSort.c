#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int* arr;
    int size;
    int capacity;
    int k;  // Number of children per node
    bool isMinHeap;
} KaryHeap;

// Function prototypes
KaryHeap* createKaryHeap(int k, bool isMinHeap, int capacity);
void insertKaryHeap(KaryHeap* heap, int element);
void deleteRoot(KaryHeap* heap);
void heapify(KaryHeap* heap, int i);
void buildHeap(KaryHeap* heap);
void heapSort(int* arr, int n, int k, bool isMinHeap);
void swap(int* x, int* y);
void displayArray(int* arr, int n);
void freeKaryHeap(KaryHeap* heap);

int main() {
    int n, k;
    bool isMinHeap;
    int arr[MAX];

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the number of children per node (k): ");
    scanf("%d", &k);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter 1 for ascending order or 0 for descending order: ");
    scanf("%d", &isMinHeap);

    // Perform heap sort
    heapSort(arr, n, k, isMinHeap);

    // Display sorted array
    printf("Sorted array:\n");
    displayArray(arr, n);

    return 0;
}

KaryHeap* createKaryHeap(int k, bool isMinHeap, int capacity) {
    KaryHeap* heap = (KaryHeap*)malloc(sizeof(KaryHeap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->k = k;
    heap->isMinHeap = isMinHeap;
    return heap;
}

void insertKaryHeap(KaryHeap* heap, int element) {
    if (heap->size >= heap->capacity) {
        printf("Heap is full\n");
        return;
    }
    heap->arr[heap->size] = element;
    int i = heap->size;
    heap->size++;

    // Heapify up
    while (i != 0) {
        int parent = (i - 1) / heap->k;
        if ((heap->isMinHeap && heap->arr[parent] > heap->arr[i]) ||
            (!heap->isMinHeap && heap->arr[parent] < heap->arr[i])) {
            int temp = heap->arr[parent];
            heap->arr[parent] = heap->arr[i];
            heap->arr[i] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

void deleteRoot(KaryHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return;
    }
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
}

void heapify(KaryHeap* heap, int i) {
    int extremum = i;
    int firstChild = heap->k * i + 1;

    for (int j = firstChild; j < firstChild + heap->k && j < heap->size; j++) {
        if ((heap->isMinHeap && heap->arr[j] < heap->arr[extremum]) ||
            (!heap->isMinHeap && heap->arr[j] > heap->arr[extremum])) {
            extremum = j;
        }
    }

    if (extremum != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[extremum];
        heap->arr[extremum] = temp;
        heapify(heap, extremum);
    }
}

void buildHeap(KaryHeap* heap) {
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        heapify(heap, i);
    }
}

void heapSort(int* arr, int n, int k, bool isMinHeap) {
    KaryHeap* heap = createKaryHeap(k, !isMinHeap, n);

    for (int i = 0; i < n; i++) {
        insertKaryHeap(heap, arr[i]);
    }

    buildHeap(heap);

    for (int i = n - 1; i >= 0; i--) {
        arr[i] = heap->arr[0];
        deleteRoot(heap);
    }

    freeKaryHeap(heap);
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void displayArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void freeKaryHeap(KaryHeap* heap) {
    free(heap->arr);
    free(heap);
}
