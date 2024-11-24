#include <stdio.h>
#include <stdlib.h>
#define MAX_LIMIT 100

int* alloc(int size);
void input(int* list, int size);
void mergeSort(int* list, int left, int right);
void merge(int* list, int left, int middle, int right);
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
    mergeSort(list, 0, size - 1);
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

void merge(int* list, int left, int middle, int right){
    int i = 0, j = 0, k = 0;
    int sizeA = middle - left + 1;
    int sizeB = right - middle;
    int* listA = (int*)calloc(sizeA, sizeof(int));
    int* listB = (int*)calloc(sizeB, sizeof(int)); 

    for(int i = 0; i < sizeA; i++)
        *(listA + i) = *(list + (left + i));
    for(int j = 0; j < sizeB; j++)
        *(listB + j) = *(list + (middle + j + 1));
    i = 0, j = 0, k = left;
    while(i < sizeA && j < sizeB){
        if(listA[i] < listB[j])
            list[k++] = listA[i++];
        else
            list[k++] = listB[j++];
    }

    while(i < sizeA)
        list[k++] = listA[i++];
    while(j < sizeB)
        list[k++] = listB[j++];
}

void mergeSort(int* list, int left, int right){
    if(left < right){
        int middle = (left + right) / 2;
        mergeSort(list, left, middle);
        mergeSort(list, middle + 1, right);
        merge(list, left, middle, right);
    }
}

void display(int* list, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
}