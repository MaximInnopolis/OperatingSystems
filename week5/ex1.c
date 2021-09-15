#include <stdio.h>
#include <pthread.h>

void* call(void *arg) {
    printf("Thread %d has been created.\n", *(int*)arg);
}

int main() {
    pthread_t thread;
    int N;
    printf("Enter the number of threads:");
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        printf("Creating new thread. Its number is %d\n", i);
        pthread_create(&thread, NULL, &call, &i);
        pthread_join(thread, NULL);
    }
    return 0;
}