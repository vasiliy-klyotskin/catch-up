#include <macroassert.h>
#include <unit.h>

void test_init(void) {
    double x = 5.0;
    double y = 7.0;

    Unit u = unit_init(x, y);

    assert_fp_eq(u.acceleration.x, 0);
    assert_fp_eq(u.acceleration.y, 0);
    assert_fp_eq(u.velocity.x, 0);
    assert_fp_eq(u.velocity.y, 0);
    assert_fp_eq(u.position.x, 5.0);
    assert_fp_eq(u.position.y, 7.0);
}

void tests_unit(void) {
    test_init();
}