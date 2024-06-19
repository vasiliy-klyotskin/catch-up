#include <stdio.h>

void tests_simulation();
void tests_dynamic_array();

int main() {
    tests_dynamic_array();
    tests_simulation();
    printf("All tests passed!");
    return 0;
}