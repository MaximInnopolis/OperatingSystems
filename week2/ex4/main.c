#include <stdio.h>

void separate(int *pInt, int *secound);

int main() {
    int first,secound;
    printf("Enter 1st number:\n");
    scanf("%d",&first);
    printf("Enter 2nd number:\n");
    scanf("%d",&secound);

    printf("Before swap first number = %d, secound number = %d\n", first, secound);
    separate(&first, &secound);
    printf("After swap first number = %d, secound number = %d", first, secound);
    return 0;
}

void separate(int *first, int *secound) {
    int temp;
    temp = *secound;
    *secound = *first;
    *first = temp;
}
