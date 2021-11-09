#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <errno.h>

int main() {
    const char* dev = "/dev/input/by-path/platform-i8042-serio-0-events-kbd";
    struct input_event events;
    int device = open(dev, O_RDONLY);
    read(device, &events, sizeof events);
    read(device, &events, sizeof events);
    if (device == -1) {
        fprintf(stderr, "%s does not open: %s.\n", dev, strerror(errno));
        return 1;
    }

    int buffer[BUFFER_SIZE];
    while (1) {
        read(device, &events, sizeof events);
        if (events.type == EV_KEY && events.value == 1) {
            for (int i = BUFFER_SIZE - 1; i >= 1; --i)
                buffer[i] = buffer[i - 1];
            buffer[0] = events.code;

            if (buffer[0] == KEY_E && buffer[1] == KEY_P)
                printf("I passed the Exam!\n");
            else if (buffer[0] == KEY_P && buffer[1] == KEY_A && buffer[2] == KEY_C)
                printf("Get some cappuccino!\n");
            else if (buffer[0] == KEY_A && buffer[1] == KEY_N)
                printf("Nice tasks, dear colleagues\n");
    }

    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return 0;
}