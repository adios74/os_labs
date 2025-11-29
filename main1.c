#include "area.h"
#include "integral.h"
#include "print_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char input[100];
    
    while (1) {
        print_string("Enter command: ");
        int n = read(STDIN_FILENO, input, sizeof(input) - 1);
        if (n <= 0) break;
        input[n] = '\0';
        if (input[n-1] == '\n') {
            input[n-1] = '\0';
            n--;
        }

        if (n == 0) continue;

        if (input[0] == '1') {
            float a = 0.0f, b = 0.0f;
            int count = 0;
            char *token = strtok(input + 1, " ");
            
            while (token != NULL && count < 2) {
                if (count == 0) a = atof(token);
                if (count == 1) b = atof(token);
                token = strtok(NULL, " ");
                count++;
            }
            
            if (count == 2) {
                float result = area(a, b);
                print_string("Area result: ");
                print_float(result);
                print_string("\n");
            } else {
                print_string("Error: area function requires 2 arguments\n");
            }
        }
        else if (input[0] == '2') {
            float a = 0.0f, b = 0.0f, e = 0.0f;
            int count = 0;
            char *token = strtok(input + 1, " ");
            
            while (token != NULL && count < 3) {
                if (count == 0) a = atof(token);
                if (count == 1) b = atof(token);
                if (count == 2) e = atof(token);
                token = strtok(NULL, " ");
                count++;
            }
            
            if (count == 3) {
                float result = sin_integral(a, b, e);
                print_string("Integral result: ");
                print_float(result);
                print_string("\n");
            } else {
                print_string("Error: integral function requires 3 arguments\n");
            }
        }
        else {
            print_string("Unknown command\n");
        }
    }
    
    return 0;
}