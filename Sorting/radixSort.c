#include <stdio.h>
#include <stdlib.h>
#define MAX_LIMIT 100

int* alloc(int size);
void input(int* list, int size);
void swap(int* x, int* y);
void radixSort(int* list, int size);
void display(int* list, int size);

int main(){
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
    radixSort(list, size);
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

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int getMax(int* list, int size) {
    int max = list[0];
    for(int i = 1; i < size; i++) {
        if(list[i] > max) {
            max = list[i];
        }
    }
    return max;
}

void countingSort(int* list, int size, int exp) {
    int* output = (int*)calloc(size, sizeof(int));
    int count[10] = {0};
    
    for(int i = 0; i < size; i++) {
        count[(list[i] / exp) % 10]++;
    }
    
    for(int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    for(int i = size - 1; i >= 0; i--) {
        output[count[(list[i] / exp) % 10] - 1] = list[i];
        count[(list[i] / exp) % 10]--;
    }
    
    for(int i = 0; i < size; i++) {
        list[i] = output[i];
    }
    
    free(output);
}

void radixSort(int* list, int size) {
    int max = getMax(list, size);
    
    for(int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(list, size, exp);
    }
}

void display(int* list, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}
