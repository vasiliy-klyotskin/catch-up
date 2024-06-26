#include <stdio.h>

void tests_simulation();
void tests_dynamic_array();
void tests_geometry();
void tests_unit();

int main() {
    tests_dynamic_array();
    tests_simulation();
    tests_geometry();
    tests_unit();
    printf("All tests passed!");
    return 0;
}