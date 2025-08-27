#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 1024

// Run command and capture real-time output
void run_command(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        printw("Failed to run command: %s\n", cmd);
        refresh();
        return;
    }

    char buf[BUF_SIZE];
    while (fgets(buf, sizeof(buf), fp)) {
        printw("%s", buf);
        refresh();
    }

    int ret = pclose(fp);
    if (ret != 0) {
        printw("Command exited with code %d\n", ret);
        refresh();
    } else {
        printw("Command completed successfully.\n");
        refresh();
    }

    printw("\nPress any key to continue...\n");
    getch();
}

// Prompt user for input (used for GitHub token, repo, tag)
void prompt_input(const char *prompt, char *buffer, size_t size) {
    echo();
    mvprintw(LINES - 2, 0, "%s", prompt);
    getnstr(buffer, size - 1);
    noecho();
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    const char *choices[] = {
        "Build Linux",
        "Build Windows",
        "Build Both",
        "Clean builds",
        "Package binaries",
        "Release to GitHub",
        "Run Bootstrap",
        "Exit"
    };
    int n_choices = sizeof(choices)/sizeof(choices[0]);
    int highlight = 0;
    int choice = -1;

    while(1) {
        clear();
        printw("=== Tin-LIA Build & Release Tool ===\n\n");
        for(int i = 0; i < n_choices; i++) {
            if(i == highlight) attron(A_REVERSE);
            printw("%s\n", choices[i]);
            if(i == highlight) attroff(A_REVERSE);
        }

        int c = getch();
        switch(c) {
            case KEY_UP: highlight--; if(highlight < 0) highlight = n_choices-1; break;
            case KEY_DOWN: highlight++; if(highlight >= n_choices) highlight = 0; break;
            case 10: choice = highlight; break; // Enter
        }

        if(choice != -1) {
            clear();
            switch(choice) {
                case 0: // Linux build
                    run_command("mkdir -p build-linux && cd build-linux && ../configure --with-platform=linux && make -j$(nproc)");
                    break;
                case 1: // Windows build
                    run_command("mkdir -p build-win && cd build-win && CC=x86_64-w64-mingw32-gcc ../configure --with-platform=win && make -j$(nproc)");
                    break;
                case 2: // Both
                    run_command("mkdir -p build-linux && cd build-linux && ../configure --with-platform=linux && make -j$(nproc)");
                    run_command("mkdir -p build-win && cd build-win && CC=x86_64-w64-mingw32-gcc ../configure --with-platform=win && make -j$(nproc)");
                    break;
                case 3: // Clean
                    run_command("rm -rf build-linux build-win");
                    break;
                case 4: // Package
                    run_command("zip -r build-linux/tin-lia-linux.zip build-linux/src/tin-lia build-linux/src/liblinux/liblinux.a build-linux/src/liblia/liblia.a");
                    run_command("zip -r build-win/tin-lia-win.zip build-win/src/tin-lia.exe build-win/src/libwin/libwin.a build-win/src/liblia/liblia.a");
                    break;
                case 5: // Release to GitHub
                {
                    char token[128], repo[128], tag[64];
                    prompt_input("GitHub token: ", token, sizeof(token));
                    prompt_input("Repo (owner/repo): ", repo, sizeof(repo));
                    prompt_input("Release tag (e.g., v1.0.0): ", tag, sizeof(tag));

                    // Create release
                    char curl_cmd[1024];
                    snprintf(curl_cmd, sizeof(curl_cmd),
                        "curl -H \"Authorization: token %s\" "
                        "-H \"Content-Type: application/json\" "
                        "-d '{\"tag_name\": \"%s\", \"name\": \"%s\"}' "
                        "https://api.github.com/repos/%s/releases",
                        token, tag, tag, repo);
                    run_command(curl_cmd);

                    // Upload assets
                    snprintf(curl_cmd, sizeof(curl_cmd),
                        "curl -H \"Authorization: token %s\" "
                        "-H \"Content-Type: application/zip\" "
                        "--data-binary @build-linux/tin-lia-linux.zip "
                        "https://uploads.github.com/repos/%s/releases/tags/%s/assets?name=tin-lia-linux.zip",
                        token, repo, tag);
                    run_command(curl_cmd);

                    snprintf(curl_cmd, sizeof(curl_cmd),
                        "curl -H \"Authorization: token %s\" "
                        "-H \"Content-Type: application/zip\" "
                        "--data-binary @build-win/tin-lia-win.zip "
                        "https://uploads.github.com/repos/%s/releases/tags/%s/assets?name=tin-lia-win.zip",
                        token, repo, tag);
                    run_command(curl_cmd);
                    break;
                }
                case 6: // Bootstrap
                    run_command("./bootstrap");
                    break;
                case 7: // Exit
                    endwin();
                    return 0;
            }
            choice = -1; // reset after action
        }
    }

    endwin();
    return 0;
}
