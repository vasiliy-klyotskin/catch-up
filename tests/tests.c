#include <stdio.h>

void tests_dynamic_array(void);
void tests_geometry(void);
void tests_unit(void);
void tests_collision(void);
void tests_random_accels(void);
void tests_movement(void);
void tests_players(void);

int main(void) {
    tests_dynamic_array();
    tests_geometry();
    tests_unit();
    tests_collision();
    tests_random_accels();
    tests_movement();
    tests_players();
    printf("All tests passed!");
    return 0;
}