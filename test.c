#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

void copy_name(char* input) {
    char buffer[10];
    strcpy(buffer, input);  
    printf("Name: %s\n", buffer);
}
 

int* create_array(int size) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = i * 2;
    }
    return arr;  
}
 

int multiply(int a, int b) {
    return a * b;  
}

void print_array(int* arr, int size) {
    for (int i = 0; i <= size; i++) {  
        printf("%d ", arr[i]);
    }
    printf("\n");
}
 

int calculate(int x) {
    int temp = 0;  
    return x * x;
}
 
int main() {
  
    copy_name("this is way too long for the buffer");
 
    
    int* data = create_array(5);
    print_array(data, 5);
 
   
    int result = multiply(100000, 100000);
    printf("Result: %d\n", result);
 
    return 0;
}