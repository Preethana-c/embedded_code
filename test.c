#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Bug 1: buffer overflow risk
void copy_name(char* input) {
    char buffer[10];
    strcpy(buffer, input);  // no length check
    printf("Name: %s\n", buffer);
}
 
// Bug 2: memory leak
int* create_array(int size) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = i * 2;
    }
    return arr;  // caller never frees this
}//testing PR

// Bug 3: integer overflow
int multiply(int a, int b) {
    return a * b;  // no overflow check
}

 
// Bug 4: null pointer not checked
void print_array(int* arr, int size) {
    for (int i = 0; i <= size; i++) {  // off by one error
        printf("%d ", arr[i]);
    }
    printf("\n");
}
 
// Bug 5: unused variable
int calculate(int x) {
    int temp = 0;  // never used
    return x * x;
}
 
int main() {
    // triggers buffer overflow
    copy_name("this is way too long for the buffer");
 
    // memory leak — never freed
    int* data = create_array(5);
    print_array(data, 5);
 
    // potential overflow
    int result = multiply(100000, 100000);
    printf("Result: %d\n", result);
 
    return 0;
}