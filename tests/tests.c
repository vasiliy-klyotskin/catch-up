#include <stdio.h>

void tests_simulation(void);
void tests_dynamic_array(void);
void tests_geometry(void);
void tests_unit(void);

int main(void) {
    tests_dynamic_array();
    tests_simulation();
    tests_geometry();
    tests_unit();
    printf("All tests passed!");
    return 0;
}