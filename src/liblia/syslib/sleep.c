#include <unistd.h>

void sleep_ms(int milliseconds) {
    usleep(milliseconds);
}

void sleep_s(int seconds) {
    sleep(seconds);
}
