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
void displayHeap(KaryHeap* heap);
void freeKaryHeap(KaryHeap* heap);

int main() {
    int k = 3; // Number of children per node
    KaryHeap* maxHeap = createKaryHeap(k, false, MAX); // MaxHeap
    KaryHeap* minHeap = createKaryHeap(k, true, MAX);  // MinHeap

    // MaxHeap operations
    insertKaryHeap(maxHeap, 10);
    insertKaryHeap(maxHeap, 20);
    insertKaryHeap(maxHeap, 5);
    insertKaryHeap(maxHeap, 6);
    insertKaryHeap(maxHeap, 2);
    insertKaryHeap(maxHeap, 8);

    printf("Max K-ary Heap:\n");
    displayHeap(maxHeap);

    deleteRoot(maxHeap);
    printf("Max K-ary Heap after deleting root:\n");
    displayHeap(maxHeap);

    // MinHeap operations
    insertKaryHeap(minHeap, 10);
    insertKaryHeap(minHeap, 20);
    insertKaryHeap(minHeap, 5);
    insertKaryHeap(minHeap, 6);
    insertKaryHeap(minHeap, 2);
    insertKaryHeap(minHeap, 8);

    printf("\nMin K-ary Heap:\n");
    displayHeap(minHeap);

    deleteRoot(minHeap);
    printf("Min K-ary Heap after deleting root:\n");
    displayHeap(minHeap);

    freeKaryHeap(maxHeap);
    freeKaryHeap(minHeap);

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

    // Find the extreme value among the node and its children
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

void displayHeap(KaryHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

void freeKaryHeap(KaryHeap* heap) {
    free(heap->arr);
    free(heap);
}
