#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

#define SIZE 256

typedef struct link {
    long int inum;
    int n_links;
    char **hard_links;
} link;

int main() {
    link *links = malloc(SIZE * sizeof(link));
    for (int i = 0; i < SIZE; i++) {
        links[i].inum = 0;
        links[i].n_links = 0;
        links[i].hard_links = malloc(SIZE * sizeof(char*));
        for (int j = 0; j < SIZE; j++)
            links[i].hard_links[j] = malloc(SIZE * sizeof(char));
    }
    int n_inodes = 0;

    struct stat m_stat;

    DIR *dir = opendir("tmp");
    if (dir == NULL)
        return 1;

    struct dirent *dp;
    char path[SIZE];

    strcpy(path, "tmp/");
    while ((dp = readdir(dir)) != NULL) {
        strcat(path, dp->d_name);
        stat(path, &m_stat);

        int i = 0;
        for (; i < n_inodes && links[i].inum != m_stat.st_ino; i++);
        if (links[i].inum == m_stat.st_ino) {
            strcpy(links[i].hard_links[links[i].n_links++], dp->d_name);
        } else {
            n_inodes++;
            links[i].inum = m_stat.st_ino;
            links[i].n_links = 1;
            strcpy(links[i].hard_links[0], dp->d_name);
        }

        strcpy(path, "tmp/");
    }

    for (int i = 0; i < n_inodes; i++) {
        printf("hard links for %d: ", links[i].inum);
        for (int j = 0; j < links[i].n_links; j++)
            printf("%s ", links[i].hard_links[j]);
        printf("\n");
    }

    closedir(dir);

    return 0;
}