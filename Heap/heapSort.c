#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

void heapify(int* arr, int n, int i, bool isMinHeap);
void buildHeap(int* arr, int n, bool isMinHeap);
void heapSort(int* arr, int n, bool isMinHeap);
void swap(int* x, int* y);
void displayArray(int* arr, int n);

int main() {
    int n;
    bool isMinHeap;
    int arr[MAX];

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter 1 for ascending order or 0 for descending order: ");
    scanf("%d", &isMinHeap);

    // Perform heap sort
    heapSort(arr, n, isMinHeap);

    // Display sorted array
    printf("Sorted array:\n");
    displayArray(arr, n);

    return 0;
}

void heapify(int* arr, int n, int i, bool isMinHeap) {
    int extremum = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (isMinHeap) {
        if (left < n && arr[left] < arr[extremum]) {
            extremum = left;
        }
        if (right < n && arr[right] < arr[extremum]) {
            extremum = right;
        }
    } else {
        if (left < n && arr[left] > arr[extremum]) {
            extremum = left;
        }
        if (right < n && arr[right] > arr[extremum]) {
            extremum = right;
        }
    }

    if (extremum != i) {
        swap(&arr[i], &arr[extremum]);
        heapify(arr, n, extremum, isMinHeap);
    }
}

void buildHeap(int* arr, int n, bool isMinHeap) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, isMinHeap);
    }
}

void heapSort(int* arr, int n, bool isMinHeap) {
    buildHeap(arr, n, !isMinHeap); // Build the heap with max-heap or min-heap

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, !isMinHeap); // Heapify the reduced heap
    }
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
