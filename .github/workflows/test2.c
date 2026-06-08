#include <stdio.h>
#include <string.h>

#define MAX_SENSORS 5

// Simulates reading temperature from sensors

// Bug 1: buffer overflow
void set_device_name(char* name) {
    char buffer[10];
    strcpy(buffer, name);  // no length check
    printf("Device: %s\n", buffer);
}

// Bug 2: divide by zero possible
float get_average_temp(int temps[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += temps[i];
    }
    return sum / count;  // crash if count is 0
}

// Bug 3: array out of bounds
void add_reading(int readings[], int* count, int value) {
    readings[*count] = value;
    (*count)++;  // never checks if count >= MAX_SENSORS
}

// Bug 4: uninitialized variable
void check_alert(int temp) {
    int threshold;  // garbage value
    if (temp > threshold) {
        printf("ALERT: High temperature!\n");
    }
}

// Bug 5: memory leak
int* create_log(int size) {
    int* log = malloc(size * sizeof(int));
    return log;  // caller never frees
}

int main() {
    // trigger buffer overflow
    set_device_name("TemperatureSensor_01");

    int temps[MAX_SENSORS];
    int count = 0;

    // trigger out of bounds
    for (int i = 0; i < 10; i++) {
        add_reading(temps, &count, i * 5);
    }

    // trigger divide by zero
    printf("Average: %.2f\n", get_average_temp(temps, 0));

    // trigger uninitialized variable
    check_alert(75);

    // memory leak
    int* log = create_log(10);

    return 0;
}