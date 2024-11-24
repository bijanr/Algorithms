#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int size;
} Heap;

Heap* createHeap();
void insertMaxHeap(Heap* heap, int element);
void deleteMaxHeap(Heap* heap);
void maxHeapify(Heap* heap, int i);
void displayHeap(Heap* heap);

int main() {
    Heap* maxHeap = createHeap();

    insertMaxHeap(maxHeap, 10);
    insertMaxHeap(maxHeap, 20);
    insertMaxHeap(maxHeap, 5);
    insertMaxHeap(maxHeap, 6);
    insertMaxHeap(maxHeap, 2);
    insertMaxHeap(maxHeap, 8);

    printf("Max Heap:\n");
    displayHeap(maxHeap);

    deleteMaxHeap(maxHeap);
    printf("Max Heap after deleting root:\n");
    displayHeap(maxHeap);

    free(maxHeap);
    return 0;
}

Heap* createHeap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    return heap;
}

void insertMaxHeap(Heap* heap, int element) {
    if (heap->size >= MAX) {
        printf("Heap is full\n");
        return;
    }
    heap->arr[heap->size] = element;
    int i = heap->size;
    heap->size++;
    
    // Heapify up
    while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i]) {
        int temp = heap->arr[(i - 1) / 2];
        heap->arr[(i - 1) / 2] = heap->arr[i];
        heap->arr[i] = temp;
        i = (i - 1) / 2;
    }
}

void deleteMaxHeap(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return;
    }
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
}

void maxHeapify(Heap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[largest];
        heap->arr[largest] = temp;
        maxHeapify(heap, largest);
    }
}

void displayHeap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}
