#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[], char *envp[]){
    char in[512];
    printf(">> ");
    fgets(in, 512, stdin);
    in[strlen(in)-1] = 0;
    char *cmd[16];
    for (int i = 0; i < 16; ++i){
        cmd[i] = malloc(64 * sizeof(char));
    }
    int count = 1;
    cmd[0] = strtok(in," ");
    while (cmd[count-1] != NULL){
        cmd[count] = strtok(NULL, " ");
        if (++count >= 16) break;
    }
    count--;
    if (!strcmp(cmd[count-1], "&")){
        if (fork() == 0){
            printf("[%d]\n", getpid());
            cmd[count-1] = NULL;
            execvp(cmd[0], cmd);
            exit(0);
        } else sleep(1);
    } else {
        cmd[count] = NULL;
        execvp(cmd[0], cmd);
    }
    return 0;
}