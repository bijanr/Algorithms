#include <stdio.h>
#include <stdlib.h>
#define MAX_LIMIT 100

int* alloc(int size);
void input(int* list, int size);
void swap(int* x, int* y);
void bubbleSort(int* list, int size);
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
    bubbleSort(list, size);
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

void bubbleSort(int* list, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size-i-1; j++){
            if(list[j] > list[j+1]){
                swap(&list[j], &list[j+1]);
            }
        }
    }
}

void display(int* list, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
}