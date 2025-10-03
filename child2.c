#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/limits.h>

void invertation(char* stroka, int length) {
    char* start = stroka;
    char* end = stroka + length - 1;
    while(start < end) {
        char a = *start;
        *start = *end;
        *end = a;
        start++;
        end--;
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        const char msg[] = "Wrong number of arguments\n";
        write(STDERR_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[1];
    const char* data = argv[2];
    int len = strlen(data);

    int file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (file == -1) {
        const char msg[] = "error: failed to open file 2\n";
        write(STDERR_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }

    char* inverted = malloc(len + 1);
    strcpy(inverted, data);
    invertation(inverted, len);

    write(file, inverted, len);
    write(file, "\n", 1);

    const char ans[] = "Result №2: ";
    write(STDOUT_FILENO, ans, sizeof(ans) - 1);
    write(STDOUT_FILENO, inverted, len);
    write(STDOUT_FILENO, "\n", 1);

    close(file);
    free(inverted);
    return 0;
}