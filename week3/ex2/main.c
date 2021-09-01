#include <stdio.h>

void bubble_sort(int array[], int size){
    for (int i = 0; i < size-1; ++i){
        for (int j = 0; j < size-i-1; ++j){
            if (array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void print_array(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

int main() {
    int size;

    printf("How many integer numbers does your array have? \n");
    scanf("%d", &size);

    int array[size];

    printf("Enter these numbers: \n");
    for (int i = 0; i < size; ++i){
        scanf("%d", &array[i]);
    }

    bubble_sort(array, size);
    printf("Your array has been sorted:\n");
    print_array(array, size);
}