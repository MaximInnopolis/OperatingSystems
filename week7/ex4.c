#include <stdlib.h>
#include <stdio.h>

int* my_realloc(int* array, size_t size){

    if(size == 0){
        free(array);
        return array;
    }

    int* array1 = malloc(size);

    if(array == NULL)
        return array;

    for(int i = 0; i < size/sizeof(int); ++i){
        array1[i] = array[i];
    }

    free(array);
    return array1;
}


int main(){
    int* a;
    int n1, n2;

    printf("Write size of the array:\n");
    scanf("%d", &n1);
    printf("Your array: ");
    a = malloc(n1*sizeof(int));
    for(int i = 0 ; i < n1; i++){
        printf("%d ", a[i]);
    }

    printf("\nWrite new size of the array:");
    scanf("%d", &n2);
    a = my_realloc(a, n2*sizeof(int));
    printf("New array: ");
    for(int i = 0 ; i < n2; i++){
        printf("%d ", a[i]);
    }

    return 0;
}