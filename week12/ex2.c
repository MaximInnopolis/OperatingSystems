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

    while (1) {
        read(device, &events, sizeof events);
        if(events.type != 4 && events.code != EV_SYN) {
            if (events.value == 1) fprintf(stderr, "PRESSED 0x%.4x (%d)\n", events.code, events.code);
            if (events.value == 0) fprintf(stderr, "RELEASED 0x%.4x (%d)\n~~~~~~~~~~~~\n", events.code, events.code);
        }
    }

    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return 0;
}