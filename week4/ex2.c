#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 5; ++i){
        fork();
    }
    sleep(5);
    return (0);
    /*Each parent process, using a fork() call, if successful, creates 2 child processes,
     each of which also has fork() calls, creating 2 more child processes,
     *the number of processes will be 2^n, where n is the number of calls to the fork() function
     *Therefore, in the first case there will be 2 ^ 3 = 8 processes,
     *and in the second case there will be 2 ^ 5 = 32 processes
    */
}