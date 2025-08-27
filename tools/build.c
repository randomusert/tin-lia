#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 4096

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
    clrtoeol();
    getnstr(buffer, size - 1);
    noecho();
}

// Extract release ID from JSON output (very naive)
int extract_release_id(const char *json) {
    const char *id_ptr = strstr(json, "\"id\":");
    int release_id = 0;
    if(id_ptr) {
        sscanf(id_ptr, "\"id\": %d", &release_id);
    }
    return release_id;
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
                    run_command("mkdir -p build-linux && cd build-linux && ../bootstrap && ../configure --with-platform=linux && make -j$(nproc)");
                    break;
                case 1: // Windows build
                    run_command("mkdir -p build-win && cd build-win && ../bootstrap && CC=x86_64-w64-mingw32-gcc ../configure --with-platform=win && make -j$(nproc)");
                    break;
                case 2: // Both
                    run_command("mkdir -p build-linux && cd build-linux && ../bootstrap && ../configure --with-platform=linux && make -j$(nproc)");
                    run_command("mkdir -p build-win && cd build-win && ../bootstrap && CC=x86_64-w64-mingw32-gcc ../configure --with-platform=win && make -j$(nproc)");
                    break;
                case 3: // Clean
                    run_command("rm -rf build-linux build-win");
                    break;
                case 4: // Package
                    run_command("zip -j build-linux/tin-lia-linux.zip build-linux/src/tin-lia build-linux/src/liblinux/liblinux.a build-linux/src/liblia/liblia.a");
                    run_command("zip -j build-win/tin-lia-win.zip build-win/src/tin-lia.exe build-win/src/libwin/libwin.a build-win/src/liblia/liblia.a");
                    break;
                case 5: // Release to GitHub
                {
                    char token[128], repo[128], tag[64];
                    prompt_input("GitHub token: ", token, sizeof(token));
                    prompt_input("Repo (owner/repo): ", repo, sizeof(repo));
                    prompt_input("Release tag (e.g., v1.0.0): ", tag, sizeof(tag));

                    // Create release and capture JSON
                    FILE *fp = popen(
                        "curl -s -H \"Authorization: token $TOKEN\" "
                        "-H \"Content-Type: application/json\" "
                        "-d '{\"tag_name\": \"$TAG\", \"name\": \"$TAG\"}' "
                        "https://api.github.com/repos/$REPO/releases",
                        "r");

                    char json[BUF_SIZE];
                    memset(json, 0, sizeof(json));
                    if (fp) {
                        fread(json, 1, sizeof(json)-1, fp);
                        pclose(fp);
                    }

                    // Replace env variables for popen
                    char cmd[BUF_SIZE];
                    snprintf(cmd, sizeof(cmd),
                        "curl -s -H \"Authorization: token %s\" "
                        "-H \"Content-Type: application/json\" "
                        "-d '{\"tag_name\": \"%s\", \"name\": \"%s\"}' "
                        "https://api.github.com/repos/%s/releases",
                        token, tag, tag, repo);

                    fp = popen(cmd, "r");
                    if (fp) {
                        fread(json, 1, sizeof(json)-1, fp);
                        pclose(fp);
                    }

                    int release_id = extract_release_id(json);
                    if (release_id == 0) {
                        printw("Failed to create release or parse release ID!\n");
                        getch();
                        break;
                    }

                    // Upload Linux
                    snprintf(cmd, sizeof(cmd),
                        "curl -H \"Authorization: token %s\" "
                        "-H \"Content-Type: application/zip\" "
                        "--data-binary @build-linux/tin-lia-linux.zip "
                        "https://uploads.github.com/repos/%s/releases/%d/assets?name=tin-lia-linux.zip",
                        token, repo, release_id);
                    run_command(cmd);

                    // Upload Windows
                    snprintf(cmd, sizeof(cmd),
                        "curl -H \"Authorization: token %s\" "
                        "-H \"Content-Type: application/zip\" "
                        "--data-binary @build-win/tin-lia-win.zip "
                        "https://uploads.github.com/repos/%s/releases/%d/assets?name=tin-lia-win.zip",
                        token, repo, release_id);
                    run_command(cmd);

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
