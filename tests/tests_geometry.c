#include <geometry.h>
#include <macroassert.h>

void test_dot_product() {
    Vector v3 = { 2.25, -2 };
    Vector v4 = { 3, -0.7};
    double dp2 = dot_product(&v3, &v4);
    assert_fp_eq(dp2, 8.15);
}

void test_normalized_when_vector_is_zero() {
    Vector v = { 0, 0 };

    NormalizedVector norm_v = normalized(&v);

    assert_eq(norm_v.direction.x, 0);
    assert_eq(norm_v.direction.y, 0);
    assert_eq(norm_v.magnitude, 0);
}

void test_normalized() {
    Vector v = { 3, 4 };

    NormalizedVector norm_v = normalized(&v);

    assert_fp_eq(norm_v.direction.x, 0.6);
    assert_fp_eq(norm_v.direction.y, 0.8);
    assert_fp_eq(norm_v.magnitude, 5);
}

void tests_geometry() {
    test_dot_product();
    test_normalized_when_vector_is_zero();
    test_normalized();
}