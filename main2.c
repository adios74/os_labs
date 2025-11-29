#include "print_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

typedef float (*area_func_t)(float, float);
typedef float (*sin_integral_func_t)(float, float, float);

static void *area_lib = NULL;
static void *integral_lib = NULL;
static area_func_t area_func = NULL;
static sin_integral_func_t sin_integral_func = NULL;
static int current_impl = 1;

int load_libraries(int impl) {
    if (area_lib) dlclose(area_lib);
    if (integral_lib) dlclose(integral_lib);

    if (impl == 1) {
        area_lib = dlopen("libarea1.so", RTLD_LAZY);
        integral_lib = dlopen("libintegral1.so", RTLD_LAZY);
    } else {
        area_lib = dlopen("libarea2.so", RTLD_LAZY);
        integral_lib = dlopen("libintegral2.so", RTLD_LAZY);
    }

    if (!area_lib || !integral_lib) {
        print_string("Failed to load libraries\n");
        return -1;
    }

    area_func = (area_func_t)dlsym(area_lib, "area");
    sin_integral_func = (sin_integral_func_t)dlsym(integral_lib, "sin_integral");

    if (!area_func || !sin_integral_func) {
        print_string("Failed to load functions\n");
        return -1;
    }

    return 0;
}

int main() {
    if (load_libraries(1) != 0) {
        return EXIT_FAILURE;
    }

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

        if (input[0] == '0') {
            current_impl = (current_impl == 1) ? 2 : 1;
            if (load_libraries(current_impl) == 0) {
                print_string("Switched to implementation ");
                print_string(current_impl == 1 ? "1\n" : "2\n");
            }
        }
        else if (input[0] == '1') {
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
                float result = area_func(a, b);
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
                float result = sin_integral_func(a, b, e);
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
    if (area_lib) dlclose(area_lib);
    if (integral_lib) dlclose(integral_lib);

    return 0;
}