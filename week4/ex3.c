#include <stdlib.h>
#include <stdio.h>

int main() {
    char cmd[512];
    while (1) {
        fgets(cmd,512,stdin);
        system(cmd);
    }
    return 0;
}