#include <stdio.h>

void tests_simulation(void);
void tests_dynamic_array(void);
void tests_geometry(void);
void tests_unit(void);
void tests_collision(void);
void tests_movement(void);

int main(void) {
    tests_dynamic_array();
    tests_geometry();
    tests_unit();
    tests_movement();
    tests_collision();
    printf("All tests passed!");
    return 0;
}