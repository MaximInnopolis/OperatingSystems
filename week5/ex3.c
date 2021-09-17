#include <stdio.h>
#include <pthread.h>


//Global variables below
#define sizeOfBuffer 25
int i = 0;
int buffer[sizeOfBuffer];
int count = 0;
int sleeping_consumer = 1;
int sleeping_producer = 0;

_Noreturn void* producer(){
    while (1){
        if (sleeping_producer) continue;
        buffer[count++] = 1;
        if (count == sizeOfBuffer){
            printf("Printed number %d\n", i++);
            count--;
            sleeping_producer = 1;
            sleeping_consumer = 0;
        }
    }
}

_Noreturn void* consumer(){
    while (1){
        if (sleeping_consumer) continue;
        buffer[count--] = 0;
        if (count == 0){
            count++;
            sleeping_producer = 0;
            sleeping_consumer = 1;
        }
    }
}

int main(){
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, &producer, NULL);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);
    while (1){}
}

//After 83262589 iterations occurs a fatal race condition