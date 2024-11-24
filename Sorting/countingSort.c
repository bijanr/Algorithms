#include <stdio.h>
#include <stdlib.h>
#define MAX_LIMIT 100

int* alloc(int size);
void input(int* list, int size);
void countingSort(int* list, int size);
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
    countingSort(list, size);
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

void countingSort(int* list, int size){
    int i, max = list[0];
    for(i = 1; i < size; i++){
        if(list[i] > max){
            max = list[i];
        }
    }

    int* count = (int*)calloc(max + 1, sizeof(int));
    int* output = (int*)malloc(size * sizeof(int));

    for(i = 0; i < size; i++){
        count[list[i]]++;
    }

    for(i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }

    for(i = size - 1; i >= 0; i--){
        output[count[list[i]] - 1] = list[i];
        count[list[i]]--;
    }

    for(i = 0; i < size; i++){
        list[i] = output[i];
    }

    free(count);
    free(output);
}

void display(int* list, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}
