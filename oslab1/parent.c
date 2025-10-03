#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/limits.h>

int main(int argc, char** argv) {
    char fname1[NAME_MAX];
    char fname2[NAME_MAX];
    
    const char line1[] = "Enter name of a file for process №1: ";
    write(STDOUT_FILENO, line1, sizeof(line1) - 1);
    ssize_t length1 = read(STDIN_FILENO, fname1, sizeof(fname1) - 1);
    if (length1 > 0) {
        fname1[length1 - 1] = '\0';
    } else {
        fname1[0] = '\0';
    }
    
    const char line2[] = "Enter name of a file for process №2: ";
    write(STDOUT_FILENO, line2, sizeof(line2) - 1);
    ssize_t length2 = read(STDIN_FILENO, fname2, sizeof(fname2) - 1);
    if (length2 > 0) {
        fname2[length2 - 1] = '\0';
    } else {
        fname2[0] = '\0';
    }

    char buf[4096];
    ssize_t bytes;
    const char msg[] = "Enter data: ";

    while (1) {
        write(STDOUT_FILENO, msg, sizeof(msg));
        bytes = read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if (bytes <= 0) {
            break;
        }
        buf[bytes] = '\0';
        int len = bytes;
        if (buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
            len--;
        }

        if (len == 0) {
            break;
        }
        if (len > 10) {
            pid_t pid = fork();
            if (pid == 0) {
                execl("./child2", "child2", fname2, buf, NULL);
                const char err[] = "Failed to start child2\n";
                write(STDERR_FILENO, err, sizeof(err));
                exit(EXIT_FAILURE);
            }
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                execl("./child1", "child1", fname1, buf, NULL);
                const char err[] = "Failed to start child1\n";
                write(STDERR_FILENO, err, sizeof(err));
                exit(EXIT_FAILURE);
            }
        }
        wait(NULL);
    }
    
    return 0;
}