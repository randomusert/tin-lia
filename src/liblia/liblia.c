#include "liblia.h"
#include <stdio.h>
#include <string.h>

#include "commands/testcmd.h"
#include "commands/server.h"
#include "commands/client.h"

#define CMD_MAX 256


static int read_cmd(char *out, size_t cap) {
    if (!fgets(out, cap, stdin)) return 0;       // EOF or error
    out[strcspn(out, "\r\n")] = 0;                // strip newline
    return 1;
}

//liblia init function
// This function initializes the liblia library.
void liblia_init(void) {
    // Initialization code for the library can be added here.
    // For now, we just print a message to indicate that the library has been initialized.
    printf("liblia initialized.\n");
    loop();
    
}

void loop(void) {
    // This function can be used to implement the main loop of the library.
    // For now, we just print a message to indicate that the loop is running.
    while (1)
    {
        
        char cmd[CMD_MAX];
        while (read_cmd(cmd, sizeof cmd)) {
            printf(">");
            if (strcmp(cmd, "h") == 0) {
                printf("Help - show this message\n");
                printf("q - quit\n");
                printf("shutdown - shutdown the system\n");
                printf("test - test command\n");
                printf("server - start a basic web server\n");
                printf("client - start a basic client\n");
                // Add more commands as needed
            // show help; do NOT recurse into the loop
            }
            else if (strcmp(cmd, "q") == 0) {
                printf("shutting down...\n");
                return; // exit the loop
            } else if (strcmp(cmd, "shutdown") == 0) {
                printf("Shutting down the system...\n");
                // Here you would add code to actually shut down the system.
                // For now, we just print a message.
                return;
            }
            else if (strcmp(cmd, "test") == 0) {
                testcmd();
            }
            else if (strcmp(cmd, "server") == 0)
            {
                
            }
            
             else {
                printf("Unknown command: %s\n", cmd);
            }
            
        // ...
        }
    }
       
    printf("liblia loop running.\n");
}