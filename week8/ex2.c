#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <string.h>

int main() {
	int n = 10;
    int size = n * 1024 * 1024;
    for (int i = 0; i < n; i++) {
        memset(malloc(size), 0, size);
        sleep(1);
    }

    return 0;
}