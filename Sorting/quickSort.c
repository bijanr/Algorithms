#include <stdio.h>
#include <stdlib.h>
#define MAX_LIMIT 100

int* alloc(int size);
void input(int* list, int size);
void swap(int* x, int* y);
void quickSort(int* list, int low, int high);
int partition(int* list, int low, int high);
void display(int* list, int size);

int main(){
    int* list, size;
    printf("Enter the size of the list: ");
    scanf("%d", &size);
    if(size <= 0 || size > MAX_LIMIT){
        printf("Invalid limit. \n");
        return 1;
    }
    list = alloc(size);
    printf("Enter the elements: ");
    input(list, size);
    quickSort(list, 0, size - 1);
    display(list, size);
    free(list);
    return 0;
}

int* alloc(int size){
    return (int*)calloc(size, sizeof(int));
}

void input(int* list, int size){
    for(int i = 0; i < size; i++)
        scanf("%d", &list[i]);
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void quickSort(int* list, int low, int high){
    if(low < high){
        int pi = partition(list, low, high);
        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}

int partition(int* list, int low, int high){
    int pivot = list[high];
    int i = (low - 1);
    for(int j = low; j <= high - 1; j++){
        if(list[j] < pivot){
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[high]);
    return (i + 1);
}

void display(int* list, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}
