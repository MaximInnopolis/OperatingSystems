#include <stdio.h>

int main() {
    int i, j, n;

    printf("Enter value of n:\n");
    scanf("%d", &n);

    int p = n;

    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
        {
            if (j >= p){
                printf("* ");
            } else {
                printf(" ");
            }
        }
        p--;
        printf("\n");
    }
    return 0;
}