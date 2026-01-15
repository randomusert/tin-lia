#include "init.h"
#include "../syslib/sleep.h"
#include <stdio.h>

void init_msg(void) {
    printf("kernel intialization started. please wait...\n");
    sleep_ms(600);
    printf("loading modules...\n");
    sleep_s(1);
    printf("initialization complete.\n");
}