	#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t n;

    switch (n = fork()) {
        case -1:
            printf("Creation of a process has failed\n");
            exit(1);

        default:
            printf("Hello from parent [PID - %d]\n", getpid());
            break;

        case 0:
            printf("Hello from child [PID - %d]\n", getpid());
            break;
    }
    return 0;
	/*
    Output:
    Hello from parent [PID - 108]
    Hello from child [PID - 109]
    Hello from parent [PID - 110]
    Hello from child [PID - 111]
    Hello from parent [PID - 112]
    Hello from child [PID - 113]
    Hello from parent [PID - 114]
    Hello from child [PID - 115]
    Hello from parent [PID - 116]
    Hello from child [PID - 117]
    Hello from parent [PID - 118]
    Hello from child [PID - 119]
    Hello from parent [PID - 120]
    Hello from child [PID - 121]
    Hello from parent [PID - 122]
    Hello from child [PID - 123]
    Hello from parent [PID - 124]
    Hello from child [PID - 125]
    Hello from parent [PID - 126]
    Hello from child [PID - 127]
	
Ten times the parent process creates a child process that takes over the CPU after the parent process.*/
}
