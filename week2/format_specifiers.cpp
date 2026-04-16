#include <iostream>
#include <cstdio>   
using namespace std;

int main() {
    int integer_value = 42;
    float float_value = 3.14159265f;
    double double_value = 3.14159265;
    char char_value = 'X';
    const char* string_value = "Hello, World!";

    printf("Format Specifier Practice\n");
    printf("------------------------\n\n");

    printf("Decimal: %d\n", integer_value);;
    printf("Hexidecimal: %#x\n", integer_value);
    printf("With width (5): |%5d|\n", integer_value);
    printf("Left-aligned:   |%-5d|\n", integer_value);
    printf("Default: %f\n", float_value);
    printf("With precision (2): %.2f\n", float_value);
    printf("Scientific: %e\n", float_value);
    printf("Fixed with precision (4): %.4f\n", double_value);
    printf("Character: %c\n", char_value);
    printf("String: %s\n", string_value);
    printf("String with width (20): |%20s|\n", string_value);

    return 0;
}