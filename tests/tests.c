#include <stdio.h>

void tests_dynamic_array(void);
void tests_geometry(void);
void tests_unit(void);
void tests_collision(void);

int main(void) {
    tests_dynamic_array();
    tests_geometry();
    tests_unit();
    tests_collision();
    printf("All tests passed!");
    return 0;
}