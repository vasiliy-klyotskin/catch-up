#include <macroassert.h>
#include <geometry.h>
#include <math.h>

Vector rotated_by(double radian) {
    return vector_init(cos(radian), sin(radian));
}

void test_vector_dot_product(void) {
    Vector v3 = vector_init(2.25, -2);
    Vector v4 = vector_init(3, -0.7);

    double dp2 = vector_dot_product(&v3, &v4);

    assert_fp_eq(dp2, 8.15);
}

void test_vector_normalized_when_vector_is_zero(void) {
    Vector v = vector_init(0, 0);

    NormalizedVector norm_v = vector_normalized(&v);

    assert_eq(norm_v.direction.x, 0);
    assert_eq(norm_v.direction.y, 0);
    assert_eq(norm_v.magnitude, 0);
}

void test_vector_normalized(void) {
    Vector v = vector_init(3, 4);

    NormalizedVector norm_v = vector_normalized(&v);

    assert_fp_eq(norm_v.direction.x, 0.6);
    assert_fp_eq(norm_v.direction.y, 0.8);
    assert_fp_eq(norm_v.magnitude, 5);
}

void test_vector_rotation(void) {
    Vector v = vector_init(1, 0);

    Vector rotated_v1 = vector_rotated(&v, M_PI / 2);
    assert_fp_eq(rotated_v1.x, 0);
    assert_fp_eq(rotated_v1.y, 1);

    Vector rotated_v2 = vector_rotated(&v, M_PI);
    assert_fp_eq(rotated_v2.x, -1);
    assert_fp_eq(rotated_v2.y, 0);

    Vector rotated_v3 = vector_rotated(&v, M_PI / 6);
    assert_fp_eq(rotated_v3.x, 0.86602540378);
    assert_fp_eq(rotated_v3.y, 0.5);
}

void test_vector_radian(void) {
    Vector v1;
    Vector v2;

    v1 = vector_init(1, 0);
    v2 = vector_init(1, 0);

    assert_fp_eq(vector_radian(&v1, &v2), 0);

    v1 = vector_init(1, 0);
    v2 = vector_init(-1, 0);

    assert_fp_eq(fabs(vector_radian(&v1, &v2)), M_PI);

    v1 = vector_init(-0.6, 0.8);
    v2 = vector_init(0.6, -0.8);

    assert_fp_eq(fabs(vector_radian(&v1, &v2)), M_PI);

    v1 = vector_init(1, 0);
    v2 = vector_init(0, 1);

    assert_fp_eq(vector_radian(&v1, &v2), M_PI / 2);

    v1 = vector_init(0, 1);
    v2 = vector_init(1, 0);

    assert_fp_eq(vector_radian(&v1, &v2), -M_PI / 2);

    v1 = rotated_by(M_PI * 4 / 6);
    v2 = rotated_by(-M_PI / 6);

    assert_fp_eq(vector_radian(&v1, &v2), -M_PI * 5 / 6);

    v1 = rotated_by(-M_PI / 6);
    v2 = rotated_by(M_PI * 4 / 6);
    
    assert_fp_eq(vector_radian(&v1, &v2), M_PI * 5 / 6);

    v1 = rotated_by(M_PI * 5 / 6);
    v2 = rotated_by(-M_PI * 5 / 6);

    assert_fp_eq(vector_radian(&v1, &v2), M_PI / 3);

    v1 = rotated_by(-M_PI * 5 / 6);
    v2 = rotated_by(M_PI * 5 / 6);
    
    assert_fp_eq(vector_radian(&v1, &v2), -M_PI / 3);
}

void test_vector_magnitude(void) {
    Vector v = vector_init(3, 4);

    assert_fp_eq(vector_magnitude(&v), 5);
}

void test_vector_difference(void) {
    Vector v1 = vector_init(5, 5);
    Vector v2 = vector_init(8, 7);

    Vector difference = vector_difference(&v1, &v2);

    assert_fp_eq(difference.x, 3);
    assert_fp_eq(difference.y, 2);
}

void tests_geometry(void) {
    test_vector_dot_product();
    test_vector_normalized_when_vector_is_zero();
    test_vector_normalized();
    test_vector_rotation();
    test_vector_magnitude();
    test_vector_difference();
    test_vector_radian();
}