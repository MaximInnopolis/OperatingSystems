#include <stdio.h>
#include "limits.h"
#include "float.h"

int main() {
    int a;
    float b;
    double c;
    printf("Integer=%d\n",INT_MAX);
    printf("Float=%f\n",FLT_MAX);
    printf("Double=%f\n",DBL_MAX);
    printf("Sizeof integer=%llu\n",sizeof(a));
    printf("Sizeof float=%llu\n",sizeof(b));
    printf("Sizeof double=%llu\n",sizeof(c));
    return 0;
}
