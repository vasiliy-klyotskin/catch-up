#include <geometry.h>
#include <macroassert.h>

void test_dot_product() {
    Vector v1 = { 1, 2 };
    Vector v2 = { 3, -1 };
    double dp1 = dot_product(&v1, &v2);
    assert_fp_eq(dp1, 1);

    Vector v3 = { 2.25, -2 };
    Vector v4 = { 3, -0.7};
    double dp2 = dot_product(&v3, &v4);
    assert_fp_eq(dp2, 8.15);
}

void tests_geometry() {
    test_dot_product();
}