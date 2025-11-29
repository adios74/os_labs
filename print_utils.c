#include <unistd.h>
#include <string.h>

void print_string(const char *str) {
    write(STDOUT_FILENO, str, strlen(str));
}

void print_float(float value) {
    char buffer[32];
    int integer_part = (int)value;
    float fractional_part = value - integer_part;
    
    if (fractional_part < 0) fractional_part = -fractional_part;
    
    char *p = buffer;
    if (value < 0 && integer_part == 0) {
        *p++ = '-';
    }
    
    int digits = 0;
    int temp = integer_part;
    if (temp < 0) temp = -temp;
    
    do {
        digits++;
        temp /= 10;
    } while (temp > 0);
    
    temp = integer_part;
    if (temp < 0) temp = -temp;
    
    for (int i = digits - 1; i >= 0; i--) {
        p[i] = '0' + (temp % 10);
        temp /= 10;
    }
    p += digits;
    
    *p++ = '.';
    int frac_int = (int)(fractional_part * 100 + 0.5f);
    
    p[0] = '0' + (frac_int / 10);
    p[1] = '0' + (frac_int % 10);
    p[2] = '\0';
    
    print_string(buffer);
}